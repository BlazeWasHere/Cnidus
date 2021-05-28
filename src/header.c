//          Copyright Blaze 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "header.h"

#include "utils.h"

char *create_header_string(char *header, char *value) {
    // 5: sizeof("\r\n") + sizeof(": ") + sizeof('\0')
    char *key = calloc(1, strlen(header) + strlen(value) + 5);

    concat(header, ": ", key);
    concat(key, value, key);
    concat(key, "\r\n", key);

    return key;
}

void add_header(context *ctx, char *header, char *value) {
    ctx->response_headers[ctx->response_headers_count].header = header;
    ctx->response_headers[ctx->response_headers_count].value = value;

    ctx->response_headers_count++;
}

void headers_to_array(
    struct phr_header headers[], size_t headers_len, char ***array
) {
    for (size_t i = 0; i < headers_len; i++) {
        char *key = calloc(1, 100);
        sprintf(key, "%.*s", (int)headers[i].name_len, headers[i].name);
        to_lower(key);

        array[i][0] = strdup(key);
        sprintf(key, "%.*s", (int)headers[i].value_len, headers[i].value);
        to_lower(key);
        array[i][1] = strdup(key);
        printf("name: %s value: %s\n", array[i][0], array[i][1]);
        free(key);
    }
}
