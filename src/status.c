//          Copyright Blaze 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include <stdlib.h>
#include <string.h>

#include "status.h"

#define HTTP_VERSION "HTTP/1.0 "

char *handle_status(enum status status) {
    // TODO: terrible to be hardcoding here.
    char *str = calloc(1, 100);

    strcpy(str, HTTP_VERSION);

    switch (status) {
    case OK:
        strcat(str, "200 OK");
        break;
    case NO_CONTENT:
        strcat(str, "204 No Content");
        break;
    case NOT_FOUND:
        strcat(str, "404 Not Found");
        break;
    case NOT_IMPLEMENTED:
        strcat(str, "Not Implemented");
        break;
    default:
        return NULL;
    }

    // add the trailing "\r\n"
    strcat(str, "\r\n");

    return str;
};
