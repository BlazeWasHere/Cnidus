//          Copyright Blaze 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include <ctype.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

#include "method.h"
#include "server.h"

void error(const char *str, int ret, int code) {
    if (ret == code)
        err(EXIT_FAILURE, str);
}

void sigint_handler(int signal) {
    printf("Received signal: %d ... Shutting down.\n", signal);
    cleanup();
    exit(EXIT_SUCCESS);
}

http_metadata *parse_http_line(char *http_line) {
    http_metadata *data = calloc(1, sizeof(http_metadata));
    size_t method_len, path_len;
    const char *method, *path;
    int version, i = 0;
    char *token, *_path;

    data->headers_len = sizeof(data->headers) / sizeof(data->headers[0]);
    data->ret = phr_parse_request(http_line, strlen(http_line), &method,
                                  &method_len, &path, &path_len, &version,
                                  data->headers, &data->headers_len, 0);

    data->version = calloc(1, sizeof("HTTP/1.x"));
    data->method = calloc(1, method_len + 1);
    _path = calloc(1, path_len + 1);

    // now snprintf() to "correct" the variables
    snprintf(data->method, method_len + 1, "%.*s", (int)method_len, method);
    snprintf(_path, path_len + 1, "%.*s", (int)path_len, path);
    snprintf(data->version, sizeof("HTTP/1.x"), "HTTP/1.%d", version);

    // pointer arithmetic; `data->ret` returns the position where headers end
    data->data = (char *)method + data->ret;

    while ((token = strsep(&_path, "?"))) {
        if (i == 0)
            data->path = strdup(token);
        else if (i == 1)
            // TODO(blaze): This breaks if there is more than 1 `?`
            data->query_params = strdup(token);

        i++;
    }

    return data;
}

void to_lower(char *str) {
    for (; *str; ++str)
        *str = (char)tolower(*str);
}

void concat(const char *first, const char *second, char *result) {
    size_t x = strlen(first);
    size_t y = strlen(second);

    memcpy(result, first, x);
    memcpy(result + x, second, y);
}

char ***create_2d_string_array(size_t rows, size_t columns, size_t elem_size) {
    char ***array;
    array = calloc(rows, sizeof(char *));

    for (size_t i = 0; i < rows; i++) {
        array[i] = calloc(columns, elem_size);

        for (size_t j = 0; j < sizeof(char); j++)
            // +1 = '\0'
            array[i][j] = calloc(1, sizeof(char));
    }

    return array;
}

void free_2d_string_array(char ***array, size_t rows) {
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < sizeof(char); j++)
            free(array[i][j]);

        free(array[i]);
    }

    free(array);
}

size_t get_methods_for_path(dict_t *routes, char *path, http_method_t *ret) {
    static http_method_t all_http_methods[] = {GET, POST, HEAD, PUT};
    // Bit of a hackish hardcode here, longest HTTP method is 4 chars long.
    char *key = calloc(1, strlen(path) + 4 + 1);
    size_t count = 0;

    for (size_t i = 0; i < sizeof(all_http_methods) / sizeof(http_method_t);
         i++) {
        // Copy the const char pointer so we can edit it without SIGSEGV.
        char *method = strdup(http_method_to_string(all_http_methods[i]));
        to_lower(method);
        concat(method, path, key);

        if (dict_find(*routes, key) != NULL)
            ret[count++] = all_http_methods[i];

        // 'Reset' key to not intefere with future concat()s
        memset(key, '0', strlen(key));
        free(method);
    }

    return count;
}