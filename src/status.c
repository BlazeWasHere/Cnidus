#include <string.h>
#include <stdlib.h>

#include "status.h"

#define HTTP_VERSION "HTTP/1.0 "

char *handle_status(STATUS status) {
    char *str = malloc(300);

    strcpy(str, HTTP_VERSION);

    switch (status) {
        case OK:
            strcat(str, "200 OK");
            break;
        case NOT_FOUND:
            strcat(str, "404 Not Found");
            break;
        default:
            return NULL;
    }

    // add the trailing "\r\n"
    strcat(str, "\r\n");

    return str;
};
