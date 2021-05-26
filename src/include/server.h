//          Copyright Blaze 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <netinet/in.h>
#include <stdint.h>

// context which is returned to callback functions
typedef struct {
    struct sockaddr_in *client;
    int socket;
    char *path;
    char *method;
    char *data;
    char *__key;
} context;

// internal struct for the handling of a client
struct request {
    int event_type;
    int iovec_count;
    int client_socket;
    struct iovec iov[];
};

// current supported HTTP methods
typedef enum {
    GET,
    POST,
    HEAD,
} http_method;

typedef void (*callback_t)(context*);

/* init, MUST BE CALLED */
int setup_context(uint32_t entries);
/* setup the socket which will be used for `event_loop()` */
int setup_socket(int port);
/* should be called before exiting */
void cleanup();
/* runs forever, accepting and handling new connections */
void event_loop(int socket);
void add_accept_request(
    int socket, struct sockaddr_in *client_addr, socklen_t *client_0ddr_len
);
void add_read_request(int client_socket);
void handle_client_request(struct request *req, struct sockaddr_in *client);
void add_write_request(struct request *req);
/**
 * Add a route to the internal router.
 * 
 * ```c
 *      void handle_foo(struct context ctx) { ... };
 *      ...
 *      add_route(GET, "/foo", handle_foo);
 * ```
 */
int add_route(http_method method, const char *path, callback_t value);
