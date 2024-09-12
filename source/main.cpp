#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "main.h"
#include "input_output.h"


int main(){
    FILE *input = fopen("source//Input.txt", "rb");
    Errors error = NO_ERRORS;
    struct Text onegin = {};
    onegin.filename = "source//Input.txt";
    onegin.file_pointer = input;
    error = read_from_file_to_text(&onegin);
    if (error != NO_ERRORS){
        return -1;
    }
    return 0;
}
