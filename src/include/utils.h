//          Copyright Blaze 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#pragma once

typedef struct {
    char *method;    /* GET */
    char *path;      /* /foo */
    char *version;   /* HTTP/1.0 */
} http_metadata;

/**
 * Helper to call `perror(str)` if `(ret == code)`
 */
void error(const char *str, int ret, int code);
/**
 * SIGINT/^C handler, to cleanup functions on shutdown
 */
void sigint_handler(int signal);
/**
 * Helper to get the first line from a HTTP request
 */
int get_line(const char *src, char *dest, int dest_sz);
/**
 * Helper to parse line from `get_line` to char array.
 * "GET / HTTP/1.0" -> ["GET", "/", "HTTP/1.0"]
 */
http_metadata *parse_http_line(char *http_line);
/**
 * Convert char to lower, by modifying the pointer
 */
void to_lower(char *str);
