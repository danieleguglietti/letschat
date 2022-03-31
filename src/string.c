#include "letschat/utils/string.h"

#include <stdlib.h>

uint64_t strsize(const string_t str)
{
    uint64_t size = 0;
    for(string_t ch = str; *ch != '\0'; ch++, size++);
    return size;
}

void strapp(string_t str, const char ch)
{
    uint64_t size = strsize(str);
    str = realloc(str, size + 2);
    str[size] = ch;
}

string_t strjoin(const string_t str1, const string_t str2)
{
    uint64_t size1 = strsize(str1);
    uint64_t size2 = strsize(str2);

    string_t str = malloc(size1 + size2 + 1);
    str[size1 + size2] = '\0';

    for(uint64_t i = 0; i < size1; i++)
        str[i] = str1[i];

    for(uint64_t i = 0; i < size2; i++)
        str[size1 + i] = str2[i];

    return str;
}