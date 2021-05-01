//          Copyright Blaze 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <netinet/in.h>
#include "dict.h"

/**
 * handle the http method from 1st line of a http request, 
 * returns -1 on error, 0 on success
 */
int handle_http_method(char *path, int socket, struct sockaddr_in *client, dict_t *routes);
/**
 * handle the GET http method.
 */
void get();
