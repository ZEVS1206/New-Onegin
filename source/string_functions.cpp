#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


#include "onegin.h"

Errors my_strcmp(const char *str1, const char *str2, int *answer)
{
    if (str1 == NULL || str2 == NULL){
        printf("Here\n");
        return ERROR_OF_SORTING;
    }
    while (!isalpha(*str1)){
        str1++;
    }
    while (!isalpha(*str2)){
        str2++;
    }
    while (*str1 == *str2 && *str1 != '\0'){
        str1++;
        str2++;
    }
    *answer = -(toupper(*str1) - toupper(*str2));
    return NO_ERRORS;
}

Errors change_strings(char **text, size_t i, size_t j)
{
    if (text == NULL)
    {
        return ERROR_OF_SORTING;
    }
    char *elem = text[i];
    text[i] = text[j];
    text[j] = elem;
    return NO_ERRORS;
}

Errors sort_text(struct Text *onegin)
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
                                                     &result_of_compare);
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




