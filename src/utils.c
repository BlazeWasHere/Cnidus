//          Copyright Blaze 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "utils.h"

#include "server.h"


void error(const char *str, int ret, int code) {
    if (ret == code) {
        perror(str);
    }
}

void sigint_handler(int signal) {
    printf("Received signal: %d ... Shutting down.\n", signal);
    cleanup();
    exit(0);
}

http_metadata *parse_http_line(char *http_line) {
    http_metadata *data = malloc(sizeof(http_metadata));
    size_t method_len, path_len;
    const char *method, *path;
    int version;

    data->headers_len = sizeof(data->headers) / sizeof(data->headers[0]);
    data->ret = phr_parse_request(
        http_line, strlen(http_line), &method, &method_len, &path,
        &path_len, &version, data->headers, &data->headers_len, 0
    );
    
    data->version = calloc(1, sizeof("HTTP/1.x") + 1);
    data->method = calloc(1, method_len + 1);
    data->path = calloc(1, path_len + 1);

    // now sprintf() to "correct" the variables
    sprintf(data->method, "%.*s", (int)method_len, method);
    sprintf(data->path, "%.*s", (int)path_len, path);
    sprintf(data->version, "HTTP/1.%d", version);

    // pointer arithmetic; `data->ret` returns the position where headers end
    data->data = (char *)method + data->ret;

    return data;
}

void to_lower(char *str) {
    for (; *str; ++str)
        *str = (char)tolower(*str);
}

void concat(char *first, char *second, char *result) {
    size_t x = strlen(first);
    size_t y = strlen(second);

    memcpy(result, first, x);
    memcpy(result + x, second, y);
}
