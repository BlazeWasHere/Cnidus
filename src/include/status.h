#pragma once

typedef enum {
    OK          = 200,
    NOT_FOUND   = 404,
} STATUS;

/**
 * Return a HTTP response string based on status code, may return NULL
 */
char *handle_status(STATUS stats);
