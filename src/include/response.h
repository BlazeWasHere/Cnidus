//          Copyright Blaze 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <string.h>

#include "server.h"
#include "status.h"
#include "utils.h"
#include "mime.h"

#define CACHE_SIZE 64

// routes cache
typedef struct {
    char *route;
    char *text;
    size_t len;
} cache_s;

// struct representing the prepared response 
typedef struct {
    int socket;
    char *headers;
    const char *text;
    struct request *req;
    STATUS status;
    MIME_TYPE mine;
} response;

// internal use; the routes cache struct
typedef struct {
    int count;
    cache_s cache[CACHE_SIZE];
} _cache_t;

// cache the responses of routes
_cache_t routes_cache;

/* function to return a response to the socket */
void respond(
    context *ctx, const char *text, size_t size, STATUS status, MIME_TYPE mime
);
/* function to return a prepared response to the socket */
void respond_with_response(response *res);
/* respond with a 404 NOT FOUND to the socket */
void respond_not_found(int socket);
void _cache(char *route, char *text, size_t len);

/* find index of a key in the routes cache, returns -1 on failure */
static int cache_find_index(char *route) {
    to_lower(route);

    for (int i = 0; i < CACHE_SIZE; i++) {
        if (!routes_cache.cache[i].route) {
            return -1;
        } else if (!strcmp(routes_cache.cache[i].route, route)) {
            return i;
        }
    }

    return -1;
}

/* respond with 501 NOT IMPLEMENTED to the socket */
void respond_not_implemented(int socket);
