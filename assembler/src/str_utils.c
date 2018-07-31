#include "str_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

bool String_StartsWith(char *str, char *prefix){
	return strncmp(prefix, str, strlen(prefix)) == 0;
}

// The substring memory will need to be freed.
char *String_Substring(const char *str, const int start, const int length){
    char *sub = malloc((sizeof(char*) * length) + 1);
    strncpy(sub, str + start, length);
    sub[length] = '\0';
    return sub;
}

int String_IndexOf(const char *str, const char c){
    int index = -1;
    char *sub = strchr(str, c);
    if (sub != 0){
        index = sub - str;
    }
    
    return index;
}

char *String_Trim(char *string)
{
    char *start;
    int len;
    int i;

    // strlen() will segfault if given 0
    len = (string == NULL) ? 0 : strlen(string);

    /* Find the first non whitespace char */
    for (i = 0; i < len; i++) {
        if (!isspace(string[i])) {
            break;
        }
    }

    if (i == len) {
        // string is all whitespace, return empty string
        return "";
    }

    start = &string[i];

    // remove trailing whitespace
    for (i = len; i > 0; i--) {
        if (isspace(string[i])) {
            string[i] = '\0';
        } else {
            break;
        }
    }

    return start;
}