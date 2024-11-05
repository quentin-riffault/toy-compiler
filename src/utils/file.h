#ifndef UTILS_FILE_H
#define UTILS_FILE_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

FILE *open_file(const char *filepath, const char *mode);
void close_file(FILE *fd);

#endif // UTILS_FILE_H