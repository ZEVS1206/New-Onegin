#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


#include "input_output.h"
#include "main.h"

Errors read_from_file_to_text(struct Text *onegin){
    int res = 0;
    res = stat((onegin->filename), &(onegin->statistics));
    if (res != 0 || (onegin->file_pointer) == NULL){
        return ERROR_OF_OPENING_FILE;
    }
    //printf("size-%ld\n", (onegin->statistics).st_size);
    size_t size_of_file = (onegin->statistics).st_size;
    char* buffer = (char *)calloc(size_of_file, sizeof(char));
    if (buffer == NULL){
        return ERROR_OF_READING_FROM_FILE;
    }
    assert(buffer != NULL);
    size_t result_of_reading = fread(buffer, sizeof(char), size_of_file, (onegin->file_pointer));
    for (size_t i = 0; i < size_of_file; i++){
        printf("%c", buffer[i]);
    }
    if (result_of_reading != size_of_file){
        return ERROR_OF_READING_FROM_FILE;
    }
    return NO_ERRORS;
}

