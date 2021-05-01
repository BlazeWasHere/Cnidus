#include "file.h"

int file_exists(char *path) {
    struct stat _stat;

    if (stat(path, &_stat) == -1 || !S_ISREG(_stat.st_mode))
        return 0;

    return _stat.st_size;
}
