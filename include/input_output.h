#ifndef IO_H
#define IO_H

enum Errors {
    ERROR_OF_OPENING_FILE,
    ERROR_OF_WRITING_TO_FILE,
};

Errors read_from_file_to_text(struct Text *onegin, FILE *input);
#endif

