#include "str_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int starts_with(char *str, char *prefix){
	return strncmp(prefix, str, strlen(prefix)) == 0;
}

// The substring memory will need to be freed.
char *substr(const char *str, const int start, const int length){
    char *sub = malloc((sizeof(char*) * length) + 1);
    strncpy(sub, str + start, length);
    sub[length] = '\0';
    return sub;
}

int index_of(const char *str, const char c){
    int index = -1;
    char *sub = strchr(str, c);
    if (sub != 0){
        index = sub - str;
    }
    
    return index;
}

// Shamelessly stolen from JayM on Stack Overflow...
// http://stackoverflow.com/questions/2450704/writing-string-trim-in-c
char *trim(char *string)
{
    char *temp = (char) 0;
    char *start;
    int len;
    int i;

    // strlen() will segfault if given 0
    len = string == (char) 0 ? 0 : strlen(string);

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