#include <TXLib.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <stdarg.h>


#include "input_output.h"
#include "main.h"

Errors special_printf(char *format, ...){
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
                assert(str != NULL);
                if (str == NULL){
                    return ERROR_OF_PRINTING;
                }
                itoa(i, str, 10);
                puts(str);
                free(str);
                break;
            case 's':
                s = va_arg(arg, char *);
                puts(s);
                break;
            default:
                return ERROR_OF_PRINTING;
        }
    }
    va_end(arg);
    return NO_ERRORS;
}


Errors read_from_file_to_text(struct Text *onegin){
    int res = 0;
    res = stat((onegin->filename), &(onegin->statistics));
    if (res != 0 || (onegin->file_pointer) == NULL){
        return ERROR_OF_OPENING_FILE;
    }
    //printf("size-%ld\n", (onegin->statistics).st_size);
    size_t size_of_file = (onegin->statistics).st_size;
    onegin->buffer = (char *)calloc(size_of_file, sizeof(char));
    if (onegin->buffer == NULL){
        return ERROR_OF_READING_FROM_FILE;
    }
    assert(onegin->buffer != NULL);
    size_t result_of_reading = fread(onegin->buffer, sizeof(char), size_of_file, (onegin->file_pointer));
    /*for (size_t i = 0; i < size_of_file; i++){
        if (isalpha(buffer[i])){
            printf("%c", buffer[i]);
        } else if (buffer[i] == '\r'){
            printf("\\r");
        } else{
            printf("\\n");
        }
    }*/
    int num_of_rows = 0;
    for (size_t j = 0; j < size_of_file; j++){
        if ((onegin->buffer)[j] == '\n'){
            num_of_rows++;
        }
    }
    onegin->text = (char**)calloc(num_of_rows + 2, sizeof(char*));
    if (onegin->text == NULL){
        return ERROR_OF_READING_FROM_FILE;
    }
    assert(onegin->text != NULL);

    size_t i = 0;
    int cnt = 0;
    while (i < size_of_file){
        printf("i-%d\n", i);
        while (i < size_of_file && !isalpha((onegin->buffer)[i])){
            //printf("symbol-%d\n", (onegin->buffer)[i]);
            (onegin->buffer)[i] = '\0';
            i++;
        }
        //printf("%c\n", (onegin->buffer)[i]);
        if (isalpha((onegin->buffer)[i])){
            printf("%p\n", (onegin->text)[cnt]);
            (onegin->text)[cnt] = &((onegin->buffer)[i]);
            printf("%s\n", (onegin->text)[cnt]);
            cnt++;
        }
        i++;
        while (i < size_of_file && isalpha((onegin->buffer)[i])){
            //printf("%c\n", (onegin->buffer)[i]);
            i++;
        }
    }
    printf("cnt-%d\n", cnt);
    for (int t = 0; t < cnt; t++){
        printf("%p\n", (onegin->text)[t]);
    }
    /*assert((onegin->text)[2] != NULL);
    printf("%s\n", (onegin->text)[0]);
    for (int k = 0; k < num_of_rows; k++){
        printf("k-%d\n", k);
        printf("%s\n", (onegin->text)[k]);
    }*/
    free(onegin->text);
    free(onegin->buffer);
    if (result_of_reading != size_of_file){
        return ERROR_OF_READING_FROM_FILE;
    }
    return NO_ERRORS;
}

