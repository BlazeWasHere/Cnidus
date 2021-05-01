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
