//          Copyright Blaze 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <sys/stat.h>

/**
 * Helper func to find if a file exists, returns st_size on success, 0 = false
 * On success, the `path_stat` param pointer is filled.
 */
int file_exists(char *path);
