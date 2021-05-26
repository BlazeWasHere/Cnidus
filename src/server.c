//          Copyright Blaze 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include <liburing.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // close()
#include <stdio.h>

#include "server.h"

#include "method.h"
#include "utils.h"
#include "dict.h"
#include "jsmn.h"

#define READ_BUFFER     1024
#define BACKLOG         4096

// global ring
struct io_uring ring;

// global routes, maybe not do this?
dict_t routes;

int isSetup = 0;

enum {
    ACCEPT,
    READ,
    WRITE,
};

int setup_context(uint32_t entries) {
    isSetup = 1;
    routes = dict_new();
    return io_uring_queue_init(entries, &ring, 0);
}

int setup_socket(int port) {
    struct sockaddr_in address;
    int ret;

    int sock = socket(PF_INET, SOCK_STREAM, 0);
    error("socket", sock, -1);

    int optval = 1;

    ret = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    error("setsockopt", ret, -1);

    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = htonl(INADDR_ANY);

    ret = bind(sock, (struct sockaddr *)&address, sizeof(address));
    error("bind", ret, 1);

    ret = listen(sock, BACKLOG);
    error("listen", ret, -1);

    return sock;
}

void cleanup() {
    dict_free(routes);
    io_uring_queue_exit(&ring);
}

void event_loop(int srv_socket) {
    struct sockaddr_in client_addr;
    struct io_uring_cqe *cqe;
    socklen_t client_addr_len = sizeof(client_addr);

    add_accept_request(srv_socket, &client_addr, &client_addr_len);

    while (1) {
        int ret = io_uring_wait_cqe(&ring, &cqe);
        error("io_uring_wait_sqe", ret, -1);

        struct request *req = (struct request *)cqe->user_data;

        switch (req->event_type) {
            case ACCEPT:
                add_accept_request(srv_socket, &client_addr, &client_addr_len);
                add_read_request(cqe->res);
                break;

            case READ:
                if (!cqe->res) {
                    // empty res from the client, maybe they write later so break
                    break;
                }

                handle_client_request(req, &client_addr);
                break;

            case WRITE:                
                for (int i = 0; i < req->iovec_count; ++i) {
                    free(req->iov[i].iov_base);
                }

                close(req->client_socket);
                break;

            default:
                break;
        }

        io_uring_cqe_seen(&ring, cqe);
        free(req);
    }
}

void add_accept_request(int socket, struct sockaddr_in *client_addr, socklen_t *client_addr_len) {
    struct io_uring_sqe *sqe = io_uring_get_sqe(&ring);
    io_uring_prep_accept(sqe, socket, (struct sockaddr *)client_addr, client_addr_len, 0);

    struct request *req = malloc(sizeof(*req));
    req->event_type = ACCEPT;

    io_uring_sqe_set_data(sqe, req);
    io_uring_submit(&ring);
}

void add_read_request(int client_socket) {
    struct request *req = malloc(sizeof(*req) + sizeof(struct iovec));
    struct io_uring_sqe *sqe = io_uring_get_sqe(&ring);

    req->iovec_count = 1;
    req->iov[0].iov_base = calloc(1, READ_BUFFER);
    req->iov[0].iov_len = READ_BUFFER;
    req->event_type = READ;
    req->client_socket = client_socket;

    io_uring_prep_readv(sqe, client_socket, &req->iov[0], 1, 0);
    io_uring_sqe_set_data(sqe, req);
    io_uring_submit(&ring);
}

void handle_client_request(struct request *req, struct sockaddr_in *client) {
    handle_http_method(req->iov[0].iov_base, req->client_socket, client, &routes);
}

void add_write_request(struct request *req) {
    struct io_uring_sqe *sqe = io_uring_get_sqe(&ring);

    req->event_type = WRITE;

    io_uring_prep_writev(sqe, req->client_socket, req->iov, req->iovec_count, 0);
    io_uring_sqe_set_data(sqe, req);
    io_uring_submit(&ring);
}

int add_route(http_method method, const char *path, callback_t value) {
    if (isSetup == 0) {
        fprintf(stderr, "setup_context() has not been called.\n");
        return -1;
    }

    const char *method_str = http_method_to_string(method);
    char *key = calloc(1, strlen(path) + strlen(method_str) + 1);
    concat((char*)method_str, (char*)path, key);

    dict_add(routes, key, value);
    free(key);

    // add HEAD support on GET routes
    if (method == GET) {
        key = calloc(1, strlen(path) + sizeof("head") + 1);
        concat((char*)"head", (char*)path, key);
        
        dict_add(routes, key, value);
        free(key);
    } 


    return 0;
}
