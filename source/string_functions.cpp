#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


#include "onegin.h"

static Errors my_strcmp(const struct Row str1, const struct Row str2, int *answer, Compare_mode mode);
static Errors change_strings(Row *text, size_t i, size_t j);

static Errors my_strcmp(const struct Row str1, const struct Row str2, int *answer, Compare_mode mode)
{
    if (str1.start_pointer == NULL ||
        str1.end_pointer   == NULL ||
        str2.start_pointer == NULL ||
        str2.end_pointer   == NULL)
    {
        // printf("str1.start_pointer-%p\n str1.end_pointer-%p\n str2.start_pointer-%p\n str2.end_pointer-%p\n",
        //         str1.start_pointer,
        //         str1.end_pointer,
        //         str2.start_pointer,
        //         str2.end_pointer);
        return ERROR_OF_SORTING;
    }
    if (mode == FORWARD)
    {
        char *s1 = str1.start_pointer;
        char *s2 = str2.start_pointer;
        while (!isalpha(*s1))
        {
            s1++;
        }
        while (!isalpha(*s2))
        {
            s2++;
        }
        while (*s1 == *s2 && *s1 != '\0')
        {
            s1++;
            s2++;
        }
        *answer = -(toupper(*s1) - toupper(*s2));
    } else
    {
        char *s1_end = str1.end_pointer;
        char *s2_end = str2.end_pointer;
        char *s1_st  = str1.start_pointer;
        while (!isalpha(*s1_end))
        {
            s1_end--;
        }
        while (!isalpha(*s2_end))
        {
            s2_end--;
        }
        while (*s1_end == *s2_end && *s1_end != *s1_st)
        {
            s1_end--;
            s1_end--;
        }
        *answer = -(toupper(*s1_end) - toupper(*s2_end));
    }
    return NO_ERRORS;
}

static Errors change_strings(Row *text, size_t i, size_t j)
{
    if (text == NULL)
    {
        return ERROR_OF_SORTING;
    }
    char *elem = (text[i]).start_pointer;
    (text[i]).start_pointer = (text[j]).start_pointer;
    (text[j]).start_pointer = elem;
    return NO_ERRORS;
}

Errors sort_text(struct Text *onegin, Compare_mode mode)
{
    if (onegin == NULL)
    {
        return ERROR_OF_SORTING;
    }
    Errors error = NO_ERRORS;
    for (size_t i = 0; i < (onegin->text_len); i++)
    {
        //printf("i-%u\n", i);
        for (size_t j = 0; j < (onegin->text_len); j++)
        {
            //printf("j-%u\n", j);
            if (i != j)
            {
                int result_of_compare = 0;
                error = my_strcmp((onegin->text)[i], (onegin->text)[j],
                                                     &result_of_compare, mode);
                //printf("result_of_compare-%d\n", result_of_compare);
                //printf("first_compare_str-%s\n", (onegin->text)[i]);
                //printf("second_compare_str-%s\n", (onegin->text)[j]);

                if (error != NO_ERRORS)
                {
                    return error;
                }
                if (result_of_compare >= 0)
                {
                    error = change_strings(onegin->text, i, j);
                    //printf("%s\n%s\n", (onegin->text)[i], (onegin->text)[j]);
                    if (error != NO_ERRORS)
                    {
                        return error;
                    }
                }
                //printf("first_changed_str-%s\n", (onegin->text)[i]);
                //printf("second_changed_str-%s\n", (onegin->text)[j]);
            }
        }
    }
    return error;
}




