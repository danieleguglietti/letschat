#include "letschat/utils/string.h"

#include <stdlib.h>
#include <ctype.h>

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
    string_t new = (string_t) realloc(*source, sizeof(*new) * size);

    if (IS_NULL(new))
    {
        return NULL;
    }

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
    string_t sub = strinit(strsize(str + start), 0);

    if (IS_NULL(sub))
    {
        return NULL;
    }

    strcopy(str + start, sub);

    return sub;
}

string_t subnstr(const string_t str, const uint64_t start, const uint64_t size)
{
    string_t sub = strinit(size, 0);
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
    string_t new = strinit(strsize(str), 0);
    if (IS_NULL(new))
    {
        return NULL;
    }

    strcopy(str, new);
    return new;
}

bool streq(const string_t str1, const string_t str2)
{
    for(char *ch1 = str1, *ch2 = str2; *ch1 != '\0' && *ch2 != '\0'; ch1++, ch2++)
    {
        if (*ch1 != *ch2)
        {
            return false;
        }
    }

    return true;
}

bool streq_nocase(const string_t str1, const string_t str2)
{
    for(char *ch1 = str1, *ch2 = str2; *ch1 != '\0' && *ch2 != '\0'; ch1++, ch2++)
    {
        if (tolower(*ch1) != tolower(*ch2))
        {
            return false;
        }
    }

    return true;
}

string_t strinit(uint64_t size, const char ch)
{
    string_t str = (string_t) malloc(sizeof(*str) * (size + 1));
    if (IS_NULL(str))
    {
        return NULL;
    }

    strfill(str, ch, size);
    str[size] = '\0';

    return str;
}

void strfill(string_t str, const char ch, uint64_t size)
{
    while(size--)
    {
        *str++ = ch;
    }
}
