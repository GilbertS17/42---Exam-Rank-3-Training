#ifndef GET_NEXT_LINE
#define GET_NEXT_LINE

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1024
#endif

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

char *get_next_line(int fd);

#endif