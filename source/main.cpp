#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "main.h"
#include "input_output.h"
#include "string_functions.h"


int main()
{
    FILE *input = fopen("source//Input.txt", "rb");
    Errors error = NO_ERRORS;
    struct Text onegin = {};
    onegin.filename = "source//Input.txt";
    onegin.file_pointer = input;
    error = read_from_file_to_text(&onegin);
    //error = special_printf("%y\n\0", "abcd");
    if (error != NO_ERRORS)
    {
        printf("%d\n", error);
        return -1;
    }
    error = sort_text(&onegin);
    if (error != NO_ERRORS)
    {
        printf("%d\n", error);
        return -1;
    }
    //error = change_strings(onegin.text, 0, 1);
    //printf("%s\n%s\n", (onegin.text)[0], (onegin.text)[1]);
    error = print_to_console(&onegin);
    if (error != NO_ERRORS)
    {
        printf("%d\n", error);
        return -1;
    }
    return 0;
}
