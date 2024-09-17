#ifndef IO_H
#define IO_H

enum Errors
{
    ERROR_OF_SORTING           = -5,
    ERROR_OF_PRINTING          = -4,
    ERROR_OF_READING_FROM_FILE = -3,
    ERROR_OF_OPENING_FILE      = -2,
    ERROR_OF_WRITING_TO_FILE   = -1,
    NO_ERRORS                  =  0
};

Errors read_from_file_to_text(struct Text *onegin);
Errors special_printf(char *format, ...);
Errors print_to_console(struct Text *onegin);
#endif

