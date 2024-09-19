#ifndef ST_F_H
#define ST_F_H
#include "input_output.h"

enum Compare_mode
{
    FORWARD = 0,
    REVERSE = 1
};

struct Row
{
    char *start_pointer;
    char *end_pointer;
};


Errors my_strcmp(const struct Row str1, const struct Row str2, int *answer, Compare_mode mode);
Errors change_strings(Row *text, size_t i, size_t j);
Errors sort_text(struct Text *onegin);

#endif
