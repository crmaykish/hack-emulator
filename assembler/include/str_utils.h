#ifndef STR_UTILS_H
#define STR_UTILS_H

#include <stdbool.h>

/**
 * @brief Return the index of a given character
 * 
 * @param str String to search
 * @param c char to search for
 * @return int first index of c in str or -1 if not found
 */
int String_IndexOf(const char *str, const char c);

/**
 * @brief Return true if the str starts with prefix
 * 
 * @param str String to search
 * @param prefix substring to look for
 */
bool String_StartsWith(char *str, char *prefix);

/**
 * @brief Return a substring of str, starting at start and length long
 * 
 * @note Return value must be freed
 * 
 * @param str String to cut
 * @param start starting position in str
 * @param length length of substring
 * @return char* new substring
 */
char *String_Substring(const char *str, const int start, const int length);

char *String_Trim(char *string);

#endif