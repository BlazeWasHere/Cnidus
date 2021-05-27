//          Copyright Blaze 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "response.h"

#include "status.h"

#define SERVER_STR "Server: Cnidus/0.2.0\r\n"

_cache_t routes_cache;

void respond(
    context *ctx, const char *text, size_t size, 
    STATUS status, MIME_TYPE mime, int cache
) {
    char *str = handle_status(status);
    // TODO: terrible to be hardcoding here.
    str = realloc(str, size + 100);

    if (str == NULL) {
        fprintf(stderr, "Unsupported HTTP Status code: %d\n", status);
        return;
    }

    struct request *req = malloc(sizeof(*req) + sizeof(struct iovec));
    size_t text_len = strlen(text);

    sprintf(str + strlen(str), "content-length: %ld\r\n", text_len);
    
    char *content_type = calloc(1, 100);
    
    strcat(content_type, "content-type: ");
    strcat(content_type, mime_string(mime));
    strcat(str, content_type);
    strcat(str, SERVER_STR); 

    // add trailing "\r\n" to signal end of headers
    strcat(str, "\r\n");

    // remove body on HEAD
    if (strcmp(ctx->method, "head") != 0) {
        strcat(str, text);
    }

    size_t str_len = strlen(str);

    req->iovec_count = 1;
    req->iov[0].iov_base = malloc(str_len);
    req->iov[0].iov_len = str_len;
    req->client_socket = ctx->socket;
    memcpy(req->iov[0].iov_base, str, str_len);

    add_write_request(req);
    
    if (cache == 1) {
        _cache(ctx->__key, str, str_len);
    }

    free(content_type);
    free(str);
}

void respond_with_response(response *res) {
    char *str = handle_status(res->status);

    if (str == NULL) {
        fprintf(stderr, "Unsupported HTTP Status code: %d\n", res->status);
        return;
    }

    // we assume user did everything correct, not the best assumption.
    add_write_request(res->req);

    free(res->headers);
}

void respond_not_found(int socket) {
    // all hardcoded stuff here.

    struct request *req = malloc(sizeof(*req) + sizeof(struct iovec));
    const char *str = "HTTP/1.0 404 Not Found\r\n"
                "\r\n"
                "Not Found";
    
    size_t len = strlen(str);

    req->iovec_count = 1;
    req->client_socket = socket;
    req->iov[0].iov_base = malloc(len);
    req->iov[0].iov_len = len;
    memcpy(req->iov[0].iov_base, str, len);

    add_write_request(req);
} 

void _cache(char *route, char *text, size_t len) {
    cache_s cache = {
        .route = strdup(route),
        .text = strdup(text),
        .len = len
    };

    routes_cache.cache[routes_cache.count++] = cache;
}

void respond_not_implemented(int socket) {
    // all hardcoded stuff here.

    struct request *req = malloc(sizeof(*req) + sizeof(struct iovec));
    const char *str = "HTTP/1.0 501 Not Implemented\r\n"
                "\r\n"
                "Not Implemented";
    
    size_t len = strlen(str);

    req->iovec_count = 1;
    req->client_socket = socket;
    req->iov[0].iov_base = malloc(len);
    req->iov[0].iov_len = len;
    memcpy(req->iov[0].iov_base, str, len);

    add_write_request(req);
}

int cache_find_index(char *route) {
    to_lower(route);

    for (int i = 0; i < CACHE_SIZE; i++) {
        if (!routes_cache.cache[i].route) {
            return -1;
        } else if (strcmp(routes_cache.cache[i].route, route) == 0) {
            return i;
        }
    }

    return -1;
}
