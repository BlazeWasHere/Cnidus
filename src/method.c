#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h> /* printf */

#include "method.h"

#include "response.h"
#include "server.h"
#include "utils.h"

int handle_http_method(
    char *path, int socket, struct sockaddr_in *client, dict_t *routes
) {
    http_metadata *metadata = parse_http_line(path);
    to_lower(metadata->method);

    if (!metadata->method)
        return -1;

    // check if path exists in routes
    to_lower(metadata->path);
    callback_t ret = dict_find(*routes, metadata->path);

    if (ret != NULL) {
        // call the callback
        context *ctx = malloc(sizeof(context));

        ctx->method = metadata->method;
        ctx->path = metadata->path;
        ctx->client = client;
        ctx->socket = socket;

        ret(ctx);
        free(ctx);
    } else {
        // 404
        respond_not_found(socket);
    }

    free(metadata);

    return 0;
}
