#ifndef ONEGIN_H
#define ONEGIN_H
#include "input_output.h"
#include "string_functions.h"

struct Text
{
    char **text;
    char *buffer;
    size_t text_len;
    const char *filename;
    FILE *file_pointer;
};

#endif

