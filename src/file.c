//          Copyright Blaze 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include "file.h"

int file_exists(char *path) {
    struct stat _stat;

    if (stat(path, &_stat) == -1 || !S_ISREG(_stat.st_mode))
        return 0;

    return _stat.st_size;
}
