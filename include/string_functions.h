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

Errors sort_text(struct Text *onegin, Compare_mode mode);

#endif
