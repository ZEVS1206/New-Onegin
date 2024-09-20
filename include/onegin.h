#ifndef ONEGIN_H
#define ONEGIN_H
#include "input_output.h"
#include "string_functions.h"

struct Text
{
    Row *text;
    char *buffer;
    size_t text_len;
    const char *filename;
    FILE *file_pointer;
    size_t size_of_file;
};

#endif

