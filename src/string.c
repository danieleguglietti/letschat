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