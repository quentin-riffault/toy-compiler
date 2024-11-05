#include "utils/file.h"

FILE *open_file(const char *filepath, const char *mode) {

  FILE *fd = fopen(filepath, mode);

  fprintf(stdout, "[open_file] is %p\n", (void *)fd);

  if (fd == NULL) {
    fprintf(stderr, "[open_file] Could not open file %s with error %d",
            filepath, errno);
    exit(errno);
  }

  return fd;
}

void close_file(FILE *fd) {
  if (fclose(fd)) {
    fprintf(stderr, "[close_file] Could not close file descriptor (errno %d)\n",
            errno);
    exit(errno);
  }
}