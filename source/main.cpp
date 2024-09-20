#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "onegin.h"
static Errors onegin_constructor(const char *filename, struct Text *onegin);
static Errors onegin_destructor(struct Text *onegin);

int main()
{
    Errors error = NO_ERRORS;
    struct Text onegin = {};
    Compare_mode mode = FORWARD;
    error = onegin_constructor("source//Input.txt", &onegin);
    if (error != NO_ERRORS)
    {
        error = onegin_destructor(&onegin);
        fprintf(stderr, "%d\n", error);
        return -1;
    }
    error = read_from_file_to_text(&onegin);
    //printf("Here\n");
    //error = special_printf("%y\n\0", "abcd");
    if (error != NO_ERRORS)
    {
        onegin_destructor(&onegin);
        fprintf(stderr, "%d\n", error);
        return -1;
    }
    //printf("Here\n");
    error = sort_text(&onegin, mode);
    if (error != NO_ERRORS)
    {
        onegin_destructor(&onegin);
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
        onegin_destructor(&onegin);
        fprintf(stderr, "%d\n", error);
        return -1;
    }
    error = onegin_destructor(&onegin);
    if (error != NO_ERRORS)
    {
        fprintf(stderr, "AAAAAAA, WHAT IS GOING ON! STOP IT, PLEASE!\n");
        return -1;
    }
    fclose(onegin.file_pointer);
    return 0;
}


static Errors onegin_constructor(const char *filename, struct Text *onegin)
{
    if (filename == NULL || onegin == NULL)
    {
        return ERROR_OF_READING_FROM_FILE;
    }
    onegin->filename = filename;
    onegin->file_pointer = fopen(filename, "rb");
    return NO_ERRORS;
}

static Errors onegin_destructor(struct Text *onegin)
{
    if (onegin == NULL)                                                                                 onegin = NULL;
    {
        return ERROR_OF_DESTRUCTION;
    }
    for (size_t i = 0; i < (onegin->text_len); i++)
    {
        (onegin->text)[i].start_pointer = NULL;
        (onegin->text)[i].end_pointer = NULL;
    }
    for (size_t i = 0; i < (onegin->size_of_file); i++)
    {
        (onegin->buffer)[i] = '\0';
    }
    free(onegin->buffer);
    free(onegin->text);
    fclose(onegin->file_pointer);
    free(onegin);
    return NO_ERRORS;
}
