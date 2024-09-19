#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "onegin.h"
static Errors onegin_constructor(const char *filename, FILE *file_pointer, struct Text *onegin);

int main()
{
    Errors error = NO_ERRORS;
    FILE *input = fopen("source//Input.txt", "rb");
    if (input == NULL)
    {
        fprintf(stderr, "%d\n", error);
        return -1;
    }
    struct Text onegin = {};
    error = onegin_constructor("source//Input.txt", input, &onegin);
    if (error != NO_ERRORS)
    {
        fprintf(stderr, "%d\n", error);
        return -1;
    }
    error = read_from_file_to_text(&onegin);
    //printf("Here\n");
    //error = special_printf("%y\n\0", "abcd");
    if (error != NO_ERRORS)
    {
        fprintf(stderr, "%d\n", error);
        return -1;
    }
    //printf("Here\n");
    error = sort_text(&onegin);
    if (error != NO_ERRORS)
    {
        fprintf(stderr, "%d\n", error); // FIXME: stderr
        return -1;
    }
    //error = change_strings(onegin.text, 0, 1);
    //printf("%s\n%s\n", (onegin.text)[0], (onegin.text)[1]);
    /*error = print_to_console(&onegin);  // нужна функция!
    if (error != NO_ERRORS)
    {
        fprintf(stderr, "%d\n", error);
        return -1;
    }*/
    error = output_text_to_file(&onegin);
    if (error != NO_ERRORS)
    {
        fprintf(stderr, "%d\n", error);
        return -1;
    }
    // onegin_destructor();
    return 0;
}


static Errors onegin_constructor(const char *filename, FILE *file_pointer, struct Text *onegin)
{
    if (filename == NULL || file_pointer == NULL || onegin == NULL)
    {
        return ERROR_OF_READING_FROM_FILE;
    }
    onegin->filename = filename;
    onegin->file_pointer = file_pointer;
    return NO_ERRORS;
}
