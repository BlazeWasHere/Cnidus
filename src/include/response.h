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

typedef struct {
    int socket;
    char *headers;
    const char *text;
    struct request *req;
    STATUS status;
    MIME_TYPE mine;
} response;

typedef struct {
    int count;
    cache_s cache[CACHE_SIZE];
} _cache_t;

// cache the responses of routes
_cache_t routes_cache;

void respond(
    int socket, char* path, const char *text, size_t size, 
    STATUS status, MIME_TYPE mime
);
void respond_with_response(response *res);
void respond_not_found(int socket);
void _cache(char *route, char *text, size_t len);

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

void respond_not_implemented(int socket);
