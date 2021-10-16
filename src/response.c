//          Copyright Blaze 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "response.h"

#include "header.h"
#include "status.h"

#define SERVER_STR "Server: Cnidus/0.2.2\r\n"

_cache_t routes_cache;

void respond(context_t *ctx, const char *text, size_t size, enum status status,
             enum mime mime, bool cache) {
    char *str = handle_status(status);
    // TODO: terrible to be hardcoding here.
    size += 100;
    str = realloc(str, size);

    if (str == NULL) {
        fprintf(stderr, "Unsupported HTTP Status code: %d\n", status);
        return;
    }

    struct request *req =
        calloc(1, sizeof(struct request) + sizeof(struct iovec));
    size_t text_len = strlen(text);

    sprintf(str + strlen(str), "content-length: %ld\r\n", text_len);

    const char *mime_str = mime_string(mime);
    char *content_type =
        calloc(1, strlen(mime_str) + strlen("content_type: ") + 1);

    strcat(content_type, "content-type: ");
    strcat(content_type, mime_str);
    strcat(str, content_type);
    strcat(str, SERVER_STR);

    if (ctx->response_headers_count > 0) {
        struct headers *x;
        char *key;

        // user has requested to add headers
        for (size_t i = 0; i < ctx->response_headers_count; i++) {
            x = &ctx->response_headers[i];
            key = create_header_string(x->header, x->value);

            str = realloc(str, (size = size + strlen(key) + 1));
            strcat(str, key);

            free(x->header);
            free(x->value);
            free(key);
        }
    }

    // add trailing "\r\n" to signal end of headers
    strcat(str, "\r\n");

    // add body if method is not HEAD
    if (strcmp(ctx->method, "head") != 0) {
        str = realloc(str, strlen(text) + size + 1);
        strcat(str, text);
    }

    size_t str_len = strlen(str);

    req->iovec_count = 1;
    req->iov[0].iov_base = calloc(1, str_len);
    req->iov[0].iov_len = str_len;
    req->client_socket = ctx->socket;
    memcpy(req->iov[0].iov_base, str, str_len);

    add_write_request(req);

    if (cache == true)
        _cache(ctx->__key, str, str_len);

    free(content_type);
    free(str);
}

// TODO(blaze): create as a util func
void respond_not_found(int socket) {
    // all hardcoded stuff here.

    struct request *req =
        calloc(1, sizeof(struct request) + sizeof(struct iovec));
    const char *str = "HTTP/1.0 404 Not Found\r\n"
                      "\r\n"
                      "Not Found";

    size_t len = strlen(str);

    req->iovec_count = 1;
    req->client_socket = socket;
    req->iov[0].iov_base = calloc(1, len);
    req->iov[0].iov_len = len;
    memcpy(req->iov[0].iov_base, str, len);

    add_write_request(req);
}

void _cache(char *route, char *text, size_t len) {
    cache_s cache = {.route = strdup(route), .text = strdup(text), .len = len};

    routes_cache.cache[routes_cache.count++] = cache;
}

void respond_not_implemented(int socket) {
    // all hardcoded stuff here.

    struct request *req =
        calloc(1, sizeof(struct request) + sizeof(struct iovec));
    const char *str = "HTTP/1.0 501 Not Implemented\r\n"
                      "\r\n"
                      "Not Implemented";

    size_t len = strlen(str);

    req->iovec_count = 1;
    req->client_socket = socket;
    req->iov[0].iov_base = calloc(1, len);
    req->iov[0].iov_len = len;
    memcpy(req->iov[0].iov_base, str, len);

    add_write_request(req);
}

void respond_not_allowed(int socket) {
    // all hardcoded stuff here.

    struct request *req =
        calloc(1, sizeof(struct request) + sizeof(struct iovec));
    const char *str = "HTTP/1.0 405 Method Not Allowed\r\n"
                      "\r\n"
                      "Method Not Allowed";

    size_t len = strlen(str);

    req->iovec_count = 1;
    req->client_socket = socket;
    req->iov[0].iov_base = calloc(1, len);
    req->iov[0].iov_len = len;
    memcpy(req->iov[0].iov_base, str, len);

    add_write_request(req);
}

int cache_find_index(char *route) {
    to_lower(route);

    for (int i = 0; i < CACHE_SIZE; i++) {
        if (!routes_cache.cache[i].route)
            return -1;
        // TODO(blaze): use strncmp()
        else if (strcmp(routes_cache.cache[i].route, route) == 0)
            return i;
    }

    return -1;
}
