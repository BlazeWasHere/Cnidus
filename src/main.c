//          Copyright Blaze 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "cnidus.h"

#define PORT 1337
#define ENTRIES 256

static void home(context_t *ctx) {
    const char *res = "welcome to cnidus!";
    respond(ctx, res, sizeof(res), OK, txt, false);
}

static void license(context_t *ctx) {
    const char *file_name = "LICENSE";
    int ret = file_exists(file_name);

    if (!ret) {
        respond_not_found(ctx->socket);
    } else {
        /* calloc is used because we don't want to return data
         in the memory we shouldn't have returned. */
        char *buffer = calloc(1, ret);

        // you should handle possible errors from the return of read_file
        read_file(file_name, buffer, ret);

        respond(ctx, buffer, ret, OK, txt, true);
        free(buffer);
    }
}

static void post(context_t *ctx) {
    printf("received: %s\n", ctx->data);
    respond(ctx, "hello", 6, OK, txt, false);
}

static void headers(context_t *ctx) {
    // 30 rows, 2 columns
    char ***array = create_2d_string_array(30, 2, sizeof(char *));
    headers_to_array(ctx->request_headers, ctx->request_headers_len, array);

    char *buffer = calloc(30 * 2, sizeof(char *));

    for (size_t i = 0; i < ctx->request_headers_len; i++) {
        strcat(buffer, array[i][0]);
        strcat(buffer, ": ");
        strcat(buffer, array[i][1]);
        strcat(buffer, "\n");
    }

    add_header(ctx, "foo", "bar");
    strcat(buffer, "\nadded the header `foo:bar` to the request");

    respond(ctx, buffer, strlen(buffer), OK, txt, false);

    free_2d_string_array(array, 30);
    free(buffer);
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
    add_route(GET, "/headers", headers);

    printf("Listening at http://localhost:%d\n", PORT);

    event_loop(socket);
}
