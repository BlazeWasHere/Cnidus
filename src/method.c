//          Copyright Blaze 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

#include "method.h"

#include "response.h"
#include "server.h"
#include "utils.h"
#include "dict.h"

int handle_http_method(
    char *path, int socket, struct sockaddr_in *client,  dict_t *routes
) {
    http_metadata *metadata = parse_http_line(path);
    to_lower(metadata->method);

    if (!metadata->method || !metadata->path) {
        free(metadata);
        return -1;
    }

    // check if path exists in routes
    to_lower(metadata->path);
    callback_t ret = dict_find(*routes, metadata->path);

    if (ret != NULL) {
        // check if we have the route cache'd
        int idx = cache_find_index(metadata->path);

        if (idx == -1) {
            // call the callback
            context *ctx = malloc(sizeof(context));

            ctx->method = metadata->method;
            ctx->path = metadata->path;
            ctx->client = client;
            ctx->socket = socket;

            ret(ctx);
            free(ctx);
        } else {
            struct request *req = malloc(sizeof(*req) + sizeof(struct iovec));
            cache_s cache = routes_cache.cache[idx];

            req->iovec_count = 1;
            req->client_socket = socket;
            req->iov[0].iov_base = malloc(cache.len);
            req->iov[0].iov_len = cache.len;
            memcpy(req->iov[0].iov_base, cache.text, cache.len);

            add_write_request(req);
        }

    } else {
        // 404
        respond_not_found(socket);
    }

    free(metadata);

    return 0;
}
