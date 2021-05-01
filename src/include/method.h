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
