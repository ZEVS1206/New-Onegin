//#include <TXLib.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <stdarg.h>
#include <sys/stat.h>


#include "onegin.h"

static Errors replace_bad_symbols(size_t size_of_file, size_t *index_of_element_in_text, char *buffer);
static Errors save_address_of_row(int *number_of_row, char **text, char *buffer, size_t *index_of_element_in_text);
static Errors skip_symbols_in_row(size_t size_of_file, size_t *index_of_element_in_text, char *buffer);

Errors special_printf(char *format, ...)
{
    char *pointer = format;
    int i = 0;
    char *s = NULL;
    int n = 0;
    int cnt = 0;
    char *str = NULL;

    va_list arg;
    va_start(arg, format);
    for (; *pointer != '\0'; pointer++){
        while (*pointer != '%'){
            putchar(*pointer);
            pointer++;
        }

        pointer++;
        switch (*pointer){
            case 'y':
                s = va_arg(arg, char *);
                while (*s != '\0' && *s != '\r'){
                    putchar(*s);
                    s++;
                }
                break;
            case 'c':
                i = va_arg(arg, int);
                putchar(i);
                break;
            case 'd':
                i = va_arg(arg, int);
                if (i < 0){
                    i = -i;
                    putchar('-');
                }
                n = i;
                while (n > 0){
                    cnt++;
                    n /= 10;
                }
                str = (char *)calloc(cnt, sizeof(char));
                //assert(str != NULL);
                /*if (str == NULL){
                    return ERROR_OF_PRINTING;
                }*/
                itoa(i, str, 10);
                puts(str);
                free(str);
                break;
            case 's':
                s = va_arg(arg, char *);
                puts(s);
                break;
            case '\\':
                pointer++;
                switch (*pointer){
                    case 'n':
                        putchar('\n');
                        break;
                    case 't':
                        putchar('\t');
                        break;
                    case '0':
                        printf("Here\n\r");
                        return NO_ERRORS;
                        break;
                    default:
                        return ERROR_OF_PRINTING;
                        break;
                }
            default:
                printf("Error\n\r");
                return ERROR_OF_PRINTING;
                break;
        }
    }
    va_end(arg);
    return NO_ERRORS;
}

static Errors replace_bad_symbols(size_t size_of_file, size_t *index_of_element_in_text, char *buffer)
{
    if (index_of_element_in_text == NULL || buffer == NULL)
    {
        return ERROR_OF_READING_FROM_FILE;
    }
    size_t ind = *index_of_element_in_text;
    while (ind < size_of_file && (buffer[ind] == '\r' ||
                                  buffer[ind] == '\n'))
    {
        //printf("i-%u\n", *index_of_element_in_text);
        //printf("symbol-%d\n", (onegin->buffer)[i]);
        buffer[ind] = '\0';
        ind++;
    }
    //printf("i-%u\n", *index_of_element_in_text);
    *index_of_element_in_text = ind;
    return NO_ERRORS;
}

static Errors save_address_of_row(int *number_of_row, char **text, char *buffer, size_t *index_of_element_in_text)
{
    if (text == NULL || buffer == NULL || number_of_row == NULL || index_of_element_in_text == NULL)
    {
        return ERROR_OF_READING_FROM_FILE;
    }
    int nor = *number_of_row;
    size_t ind = *index_of_element_in_text;
    //printf("i-%u\n", *index_of_element_in_text);
    if (isalpha(buffer[ind]))
    {
        //printf("Here\n");
        text[nor] = &(buffer[ind]);
        //printf("%s\n", text[nor]);
        //printf("%p\n", (onegin->text)[cnt]);
    }
    nor++;
    ind++;
    *number_of_row = nor;
    *index_of_element_in_text = ind;
    return NO_ERRORS;
}

static Errors skip_symbols_in_row(size_t size_of_file, size_t *index_of_element_in_text, char *buffer)
{
    size_t ind = *index_of_element_in_text;
    if (buffer == NULL || index_of_element_in_text == NULL)
    {
        return ERROR_OF_READING_FROM_FILE;
    }
    while (ind < size_of_file && buffer[ind] != '\r')
    {
            //printf("symbol-%d\n", (onegin->buffer)[i]);
            //printf("i-%d\n", i);
            //printf("ind-%d\n", ind);
            ind++;
    }
    *index_of_element_in_text = ind;
    return NO_ERRORS;
}

Errors read_from_file_to_text(struct Text *onegin)
{
    struct stat statistics = {0};
    int res = stat((onegin->filename), &statistics);
    if (res != 0 || (onegin->file_pointer) == NULL)
    {
        return ERROR_OF_OPENING_FILE;
    }
    //printf("size-%ld\n", (onegin->statistics).st_size);
    size_t size_of_file = statistics.st_size;
    onegin->buffer = (char *)calloc(size_of_file, sizeof(char));
    if (onegin->buffer == NULL)
    {
        return ERROR_OF_READING_FROM_FILE;
    }
    //assert(onegin->buffer != NULL);
    size_t result_of_reading = fread(onegin->buffer, sizeof(char), size_of_file, (onegin->file_pointer));

    if (result_of_reading != size_of_file)
    {
        return ERROR_OF_READING_FROM_FILE;
    }

    /*for (size_t i = 0; i < size_of_file; i++){
        if (isalpha(buffer[i])){
            printf("%c", buffer[i]);
        } else if (buffer[i] == '\r'){
            printf("\\r");
        } else{
            printf("\\n");
        }
    }*/
    //printf("buffer-%s\n", onegin->buffer);
    size_t num_of_rows = 1;
    for (size_t j = 0; j < size_of_file; j++){
        if ((onegin->buffer)[j] == '\n'){
            num_of_rows++;
        }
    }
    if (num_of_rows > 1)
    {
        num_of_rows--;
    }
    //printf("num_of_rows-%u\n", num_of_rows);
    onegin->text_len = num_of_rows;
    onegin->text = (char**)calloc(num_of_rows + 2, sizeof(char*));
    if (onegin->text == NULL)
    {
        return ERROR_OF_READING_FROM_FILE;
    }
    //assert(onegin->text != NULL);

    size_t index_of_element_in_text = 0;
    int number_of_row = 0;
    // Replace\n\tTo\0(...);
    // SetText(...);
    Errors error = NO_ERRORS;
    while (index_of_element_in_text < size_of_file)
    {
        error = replace_bad_symbols(size_of_file, &index_of_element_in_text, (onegin->buffer));
        if (error != NO_ERRORS)
        {
            return error;
        }
        error = save_address_of_row(&number_of_row, (onegin->text), (onegin->buffer), &index_of_element_in_text);
        if (error != NO_ERRORS)
        {
            return error;
        }
        error = skip_symbols_in_row(size_of_file, &index_of_element_in_text, (onegin->buffer));
        if (error != NO_ERRORS)
        {
            return error;
        }
    }
    //printf("cnt-%d\n", cnt);
    // for (int t = 0; t < cnt; t++){
    //     printf("%p\n", (onegin->text)[t]);
    // }
    // printf("%s\n", (onegin->text)[0]);
    /*for (int k = 0; k < num_of_rows; k++){
        printf("k-%d\n", k);
        printf("%s\n", (onegin->text)[k]);
    }*/
    /*free(onegin->text);
    free(onegin->buffer);*/
    return NO_ERRORS;
}

Errors print_to_console(struct Text *onegin)
{
    if (onegin == NULL)
    {
        return ERROR_OF_PRINTING;
    }
    for (size_t i = 0; i < (onegin->text_len); i++)
    {
        char *str = (onegin->text)[i];
        if (str == NULL)
        {
            //printf("i-%d\n", i);
            return ERROR_OF_PRINTING;
        }
        for(; *str != '\0'; str++)
        {
            printf("%c", *str); // %s
        }
        printf("\n");
    }
    return NO_ERRORS;
}

Errors output_text_to_file(struct Text *onegin)
{
    if (onegin == NULL)
    {
        return ERROR_OF_PRINTING;
    }
    FILE *out_pointer = fopen("source//Output.txt", "wb");
    size_t i = 0;
    while (i < (onegin->text_len)){
        char *string = (onegin->text)[i];
        while (*string != '\0'){
            fputc(*string, out_pointer);
            string++;
        }
        fputc('\r', out_pointer);
        fputc('\n', out_pointer);
        i++;
    }
    return NO_ERRORS;
}
