//          Copyright Blaze 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include <stdlib.h>
#include <signal.h>
#include <stdio.h>

#include "cnidus.h"

#define PORT 1337
#define ENTRIES 256

static void home(context *ctx) {
    const char *res = "welcome to cnidus!";
    respond(ctx, res, sizeof(res), OK, txt);
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
        
        respond(ctx, buffer, ret, OK, txt);
        free(buffer);
    }
}

static void post(context *ctx) {
    printf("received: %s\n", ctx->data);
    respond(ctx, "hello", 6, OK, txt);
}

int main() {
    signal(SIGINT, sigint_handler);

    int socket = setup_socket(PORT);
    int ret = setup_context(ENTRIES);

    if (ret != 0) {
        perror("setup_context");
        exit(1);
    }

    add_route(GET, "/", home);
    add_route(GET, "/license", license);
    add_route(POST, "/post", post);
    add_route(GET, "/post", post);

    printf("Listening at http://localhost:%d\n", PORT);

    event_loop(socket);
}
