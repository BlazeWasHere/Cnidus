//          Copyright Blaze 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include "server.h"
#include "status.h"
#include "mime.h"

typedef struct {
    int socket;
    char *headers;
    const char *text;
    struct request *req;
    STATUS status;
    MIME_TYPE mine;
} response;

void respond(int socket, const char *text, STATUS status, MIME_TYPE mime);
void respond_with_response(response *res);
void respond_not_found(int socket);
