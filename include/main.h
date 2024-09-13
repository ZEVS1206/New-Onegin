#ifndef MAIN_H
#define MAIN_H
#include <sys/stat.h>

struct Text {
    char **text;
    char *buffer;
    size_t text_len;
    struct stat statistics;
    const char *filename;
    FILE *file_pointer;
};

#endif
