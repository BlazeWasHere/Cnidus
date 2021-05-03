//          Copyright Blaze 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <stdio.h>

/**
 * Helper func to find if a file exists, returns st_size on success, 0 = false
 * On success, the `path_stat` param pointer is filled.
 */
size_t file_exists(char *path);
/**
 * Helper func to open and read the `file_name` and write to an alloc'd buffer
 * Returns 0 on success, -1 on failure to open file and -2 on short read.
 */
int read_file(char *file_name, char *buffer, size_t size);
