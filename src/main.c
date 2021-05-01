//          Copyright Blaze 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include <signal.h>
#include <stdio.h>

#include "response.h"
#include "status.h"
#include "server.h"
#include "utils.h"
#include "mime.h"

#define PORT 1337
#define ENTRIES 256

void home(context *ctx) {
    respond(ctx->socket, "welcome to cnidus!", OK, txt);
}

int main() {
    signal(SIGINT, sigint_handler);

    int socket = setup_socket(PORT);
    setup_context(ENTRIES);

    add_route("/", home);

    event_loop(socket);
}
