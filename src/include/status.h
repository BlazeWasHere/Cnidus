//          Copyright Blaze 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#pragma once

typedef enum {
    OK          = 200,
    NO_CONTENT  = 204,
    NOT_FOUND   = 404,
    NOT_IMPLEMENTED = 501,
} STATUS;

/**
 * Return a HTTP response string based on status code, may return NULL
 */
char *handle_status(STATUS stats);
