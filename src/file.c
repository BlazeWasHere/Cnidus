//          Copyright Blaze 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include <sys/stat.h>

#include "file.h"

size_t file_exists(char *path) {
    struct stat _stat;

    if (stat(path, &_stat) == -1 || !S_ISREG(_stat.st_mode)) {
        return 0;
    }

    return _stat.st_size;
}

int read_file(char *file_name, char *buffer, size_t size) {
    FILE *file;
    file = fopen(file_name, "r");

    if (file == NULL) {
        return -1;
    } else if (fread(buffer, 1, size, file) != size) {
        return -2;
    }

    fclose(file);
    return 0;
}