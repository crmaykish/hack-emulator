#include "str_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int starts_with(char *str, char *prefix){
	return strncmp(prefix, str, strlen(prefix)) == 0;
}

// Shamelessly stolen from JayM on Stack Overflow...
// http://stackoverflow.com/questions/2450704/writing-string-trim-in-c
// TODO: This is still segfaulting on an empty last line for some reason...
char *trim(char *string)
{
    char *start;
    int len = strlen(string);
    int i;

    /* Find the first non whitespace char */
    for (i = 0; i < len; i++) {
        if (! isspace(string[i])) {
            break;
        }
    }

    if (i == len) {
        /* string is all whitespace */
        return string;
    }

    start = &string[i];

    /* Remove trailing white space */
    for (i = len; i > 0; i--) {
        if (isspace(string[i])) {
            string[i] = '\0';
        } else {
            break;
        }
    }

    return start;
}