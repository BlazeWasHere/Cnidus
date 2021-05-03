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

int get_line(const char *src, char *dest, int dest_sz) {
    for (int i = 0; i < dest_sz; i++) {
        dest[i] = src[i];
        if (src[i] == '\r' && src[i + 1] == '\n') {
            dest[i] = '\0';
            return 0;
        }
    }

    return 1;
}

http_metadata *parse_http_line(char *http_line) {
    http_metadata *metadata = malloc(sizeof(http_metadata));
    char *token, *str;
    uint32_t count = 0;

    str = strdup(http_line);

    while ((token = strsep(&str, " "))) {
        count++;
        
        switch (count) {
            case 1:
                metadata->method = token;
                break;

            case 2:
                metadata->path = token;
                break;

            case 3:
                metadata->version = token;
                break;

            default:
                break;
        }
    }

    return metadata;
}

void to_lower(char *str) {
    for (; *str; ++str)
        *str = (char)tolower(*str);
}