//          Copyright Blaze 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

#include "method.h"

#include "response.h"
#include "server.h"
#include "utils.h"
#include "dict.h"

extern _cache_t routes_cache;

int handle_http_method(
    char *path, int socket, struct sockaddr_in *client,  dict_t *routes
) {
    http_metadata *metadata = parse_http_line(path);

    if (!metadata->method || !metadata->path || !metadata->version) {
        free(metadata);
        return -1;
    }

    char *key = calloc(1, strlen(metadata->path) + strlen(metadata->method) + 1);
    to_lower(metadata->method);

    concat(metadata->method, metadata->path, key);

    // check if we have the route cache'd
    int idx = cache_find_index(key);

    if (idx == -1) {
        // call the callback
        callback_t ret = dict_find(*routes, key);

        if (ret != NULL) {
            context *ctx = malloc(sizeof(context));

            ctx->method = metadata->method;
            ctx->path = metadata->path;
            ctx->client = client;
            ctx->socket = socket;
            ctx->__key = key;

            if (strcmp(metadata->method, "get") == 0) {
                get(ctx, ret);
            } else if (strcmp(metadata->method, "post") == 0) {
                post(ctx, ret);
            } else {
                respond_not_implemented(socket);
            }

            free(ctx);
        } else {
            // 404
            respond_not_found(socket);
        }

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

    free(metadata);
    free(key);

    return 0;
}

const char *http_method_to_string(http_method method) {
    switch (method) {
        case GET:
            return "get";
        case POST:
            return "post";
        default:
            return NULL;
    }
}

void get(context *ctx, callback_t callback) {
    callback(ctx);
}

void post(context *ctx, callback_t callback) {
    callback(ctx);
}
