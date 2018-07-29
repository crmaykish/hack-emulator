#ifndef STR_UTILS_H
#define STR_UTILS_H

int starts_with(char *str, char *prefix);
char *substr(const char *str, const int start, const int length);
int index_of(const char *str, const char c);
char *trim(char *string);

#endif