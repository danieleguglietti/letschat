#include "letschat/utils/string.h"

#include <stdlib.h>

#define IS_NULL(x) (x == NULL)

uint64_t strsize(const string_t str)
{
    uint64_t size = 0;
    for(string_t ch = str; *ch != '\0'; ch++, size++);
    return size;
}

string_t strapp(string_t* source, const string_t str)
{
    uint64_t size = strsize(*source) + strsize(str) + 1;
    string_t new = malloc(sizeof(*new) * size);

    if (IS_NULL(new))
    {
        return NULL;
    }

    strcopy(*source, new);
    strcopy(str, new + strsize(new));

    *source = new;

    return new;
}

int64_t strfind(const string_t str, const char ch)
{
    uint64_t i = 0;
    for(string_t chr = str; *chr != '\0'; chr++)
    {
        if (*chr == ch)
            return i;
        i++;
    }

    return -1;
}

void strcopy(const string_t src, string_t dest)
{
    for(const char* ch = src; *ch != '\0'; ch++, dest++)
    {
        *dest = *ch;
    }

    *dest++ = '\0';
}
