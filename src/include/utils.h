//          Copyright Blaze 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include "picohttpparser.h"

typedef struct {
    char *method;    /* HTTP method, e.g GET */
    char *path;      /* Path of the request, e.g /foo */
    char *version;   /* HTTP version, e.g HTTP/1.0 */
    int ret;         /* returns number of bytes consumed if successful, 
                      * -2 if request is partial, -1 if failed */
    int size;        /* size of the request in bytes */
    struct phr_header headers[30];
    size_t headers_len; /* Amount of headers in the request, e.g 10 */
    char *data;      /* request body data, e.g "foo=bar" */
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
 * Helper to parse line from `get_line` to char array.
 * "GET / HTTP/1.0" -> ["GET", "/", "HTTP/1.0"]
 */
http_metadata *parse_http_line(char *http_line);
/**
 * Convert a string to lower, by modifying the pointer
 */
void to_lower(char *str);
/**
 * Join first and second to result
 */
void concat(const char *first, const char *second, char *result);
/**
 * return a calloc'd pointer which is equivalent to a 2d string array space,
 * which has `rows` and `columns`, remember to free this,
 * with `free_2d_string_array(...);`
 *
 * VISUAL:
 *      [
 *            COLUMN
 *          [ "foo", "bar" ],  ROW
 *          [ "bar", "buzz" ]
 *      ]
 */
char ***create_2d_string_array(size_t rows, size_t columns, size_t elem_size);
/**
 * To clear the array created from `create_2d_string_array(...)`
 */
void free_2d_string_array(char ***array, size_t rows);
