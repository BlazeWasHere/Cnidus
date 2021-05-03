//          Copyright Blaze 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include <stdlib.h>
#include <signal.h>
#include <stdio.h>

#include "response.h"
#include "status.h"
#include "server.h"
#include "utils.h"
#include "file.h"
#include "mime.h"

#define PORT 1337
#define ENTRIES 256

static void home(context *ctx) {
    const char *res = "welcome to cnidus!";
    respond(ctx->socket, res, sizeof(res), OK, txt);
}

static void license(context *ctx) {
    char *file_name = "LICENSE";
    int ret = file_exists(file_name);

    if (!ret) {
        respond_not_found(ctx->socket);
    } else {
        // calloc beacuse we dont want to return data 
        // in the memory we shouldnt have returned.
        char *buffer = calloc(1, ret);

        // you should handle possible errors from the return of read_file
        read_file(file_name, buffer, ret);
        
        respond(ctx->socket, buffer, ret, OK, txt);
        free(buffer);
    }
}

int main() {
    signal(SIGINT, sigint_handler);

    int socket = setup_socket(PORT);
    int ret = setup_context(ENTRIES);

    if (ret != 0) {
        perror("setup_context");
        exit(1);
    }

    add_route("/", home);
    add_route("/license", license);

    printf("Listening at http://localhost:%d\n", PORT);

    event_loop(socket);
}
