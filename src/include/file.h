#pragma once

#include <sys/stat.h>

/**
 * Helper func to find if a file exists, returns st_size on success, 0 = false
 * On success, the `path_stat` param pointer is filled.
 */
int file_exists(char *path);
