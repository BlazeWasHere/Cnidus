//          Copyright Blaze 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include "server.h"

/**
 * Add a header to the response to the client.
 * Usage: `add_header(ctx, "x-response-time", "1ms")`
 */
void add_header(context *ctx, char *header, char *value);

/* Creates a calloc'd header string to be used in the socket response */
char *create_header_string(char *header, char *value);
