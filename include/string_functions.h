#ifndef ST_F_H
#define ST_F_H
#include "input_output.h"

Errors my_strcmp(const char *str1, const char *str2, int *answer);
Errors change_strings(char **text, size_t i, size_t j);
Errors sort_text(struct Text *onegin);

#endif
