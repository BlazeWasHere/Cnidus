//          Copyright Blaze 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "method.h"

#include "dict.h"
#include "header.h"
#include "response.h"
#include "server.h"
#include "utils.h"

extern _cache_t routes_cache;

int handle_http_method(char *path, int socket, struct sockaddr_in *client,
                       dict_t *routes) {
    http_metadata *metadata = parse_http_line(path);

    if (!metadata->method || !metadata->path || !metadata->version) {
        free(metadata);
        return -1;
    }

    char *key =
        calloc(1, strlen(metadata->path) + strlen(metadata->method) + 1);
    to_lower(metadata->method);

    concat(metadata->method, metadata->path, key);

    // check if we have the route cache'd
    int idx = cache_find_index(key);

    if (idx == -1) {
        // We should not expect more than 4.
        http_method_t *methods = calloc(sizeof(http_method_t), 4);
        size_t methods_len =
            get_methods_for_path(routes, metadata->path, methods);

        if (methods_len != 0) {
            // call the callback
            callback_t ret = dict_find(*routes, key);

            context_t *ctx = calloc(1, sizeof(context_t));

            ctx->request_headers =
                calloc(metadata->headers_len, sizeof(struct phr_header));
            memcpy(ctx->request_headers, metadata->headers,
                   metadata->headers_len * sizeof(struct phr_header));
            ctx->request_headers_len = metadata->headers_len;
            ctx->response_headers_count = 0;
            ctx->method = metadata->method;
            ctx->data = metadata->data;
            ctx->path = metadata->path;
            ctx->client = client;
            ctx->socket = socket;
            ctx->__key = key;

            if (strcmp(metadata->method, "options") == 0)
                options(ctx, methods, methods_len);
            else if (ret != NULL) {
                if (strcmp(metadata->method, "get") == 0)
                    get(ctx, ret);
                else if (strcmp(metadata->method, "post") == 0)
                    post(ctx, ret);
                else if (strcmp(metadata->method, "head") == 0)
                    get(ctx, ret);
                else if (strcmp(metadata->method, "put") == 0)
                    put(ctx, ret);
                else
                    respond_not_implemented(socket);
            } else {
                respond_not_allowed(socket);
            }

            free(ctx->request_headers);
            free(ctx);

        } else {
            respond_not_found(socket);
        }

        free(methods);

    } else {
        struct request *req = malloc(sizeof(*req) + sizeof(struct iovec));
        cache_s cache = routes_cache.cache[idx];

        req->iovec_count = 1;
        req->client_socket = socket;
        req->iov[0].iov_base = malloc(cache.len);
        req->iov[0].iov_len = cache.len;
        memcpy(req->iov[0].iov_base, cache.text, cache.len);

        add_write_request(req);
    }

    if (metadata->query_params != NULL)
        free(metadata->query_params);

    free(metadata->version);
    free(metadata->method);
    free(metadata->path);
    free(metadata);
    free(key);

    return 0;
}

const char *http_method_to_string(http_method_t method) {
    switch (method) {
    case GET:
        return "GET";
    case POST:
        return "POST";
    case HEAD:
        return "HEAD";
    case PUT:
        return "PUT";
    default:
        return NULL;
    }
}

void get(context_t *ctx, callback_t callback) { callback(ctx); }

void post(context_t *ctx, callback_t callback) { callback(ctx); }

void put(context_t *ctx, callback_t callback) { callback(ctx); }

void options(context_t *ctx, http_method_t *methods, size_t methods_len) {
    // Assume all `methods` are no longer than 4 chars and 2 chars for ', '
    // ... bad assumption but oh well.
    char *ret = calloc(1, methods_len * 6 + 1);

    for (size_t i = 0; i < methods_len; i++) {
        if (i != 0)
            strcat(ret, ", ");

        strcat(ret, http_method_to_string(methods[i]));
    }

    ctx->response_headers = calloc(1, sizeof(struct headers));
    add_header(ctx, "allow", ret);

    respond(ctx, "", 0, OK, null, true);
    free(ret);
}
