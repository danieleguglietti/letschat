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

void strncopy(const string_t src, string_t dest, const uint64_t size)
{
    uint64_t i = 0;

    for(const char* ch = src; *ch != '\0' && i < size; ch++, dest++, i++)
    {
        *dest = *ch;
    }

    *dest++ = '\0';
}

string_t substr(const string_t str, const uint64_t start)
{
    uint64_t size = strsize(str + start) + 1;
    string_t sub = (string_t) malloc(sizeof(*sub) * size);

    if (IS_NULL(sub))
    {
        return NULL;
    }

    strcopy(str + start, sub);

    return sub;
}

string_t subnstr(const string_t str, const uint64_t start, const uint64_t size)
{
    string_t sub = (string_t) malloc(sizeof(*sub) * (size + 1));
    if (IS_NULL(sub))
    {
        return NULL;
    }

    strncopy(str + start, sub, size);

    return sub;
}

string_t strsplit(string_t str, const char delim)
{
    if (*str == '\0')
    {
        return NULL;
    }

    int64_t index = strfind(str, delim);
    if (index == -1)
    {
        return NULL;
    }

    string_t end = str + index;
    if (*end == '\0')
    {
        return str;
    }

    *end = '\0';
    string_t tok = end + 1; 

    return tok;
}

string_t dupstr(const string_t str)
{
    uint64_t size = strsize(str) + 1;
    string_t new = malloc(sizeof(*new) * size);
    if (IS_NULL(new))
    {
        return NULL;
    }

    strcopy(str, new);
    return new;
}
