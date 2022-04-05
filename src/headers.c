#include "letschat/headers.h"
#include <stdlib.h>
#include <ctype.h>

#define IS_LONGER(x) (strsize(x) > HEADER_FIELD_MAXLEN)
#define IS_NULL(x) (x == NULL)

#define HEADER_STRING_LEN (HEADER_FIELD_MAXLEN * 2 + 2) * HEADERS_MAXCOUNT

headers_t headers_parse(const string_t raw_headers)
{
    headers_t headers = hashtable_new();
    if (IS_NULL(headers))
    {
        return NULL;
    }

    char* src = dupstr(raw_headers);
    char* start = src;

    char* header = strsplit(&src, ';');

    while (header != NULL)
    {
        string_t key = strtrim(strsplit(&header, ':'));
        string_t value = strtrim(strsplit(&header, 0));

        if (IS_NULL(key) || IS_NULL(value) || IS_LONGER(key) || IS_LONGER(value))
        {
            hashtable_free(headers);
            free(value);
            free(src);
            free(key);
            return NULL;
        }

        headers->set(headers, key,value);

        header = strsplit(&src, ';');
    }

    if (headers->size > HEADERS_MAXCOUNT)
    {
        hashtable_free(headers);
        free(src);
        return NULL;
    }

    free(start);
    return headers;
}

string_t headers_serialize(headers_t headers)
{
    string_t headers_str = strinit(1, 0);
    if (IS_NULL(headers_str))
    {
        return NULL;
    }

    hashtable_it* it = headers->iterator(headers);

    while (it->next(it))
    {
        entry_t* current = it->current;

        if (IS_LONGER(current->key) || IS_LONGER(current->value))
        {
            free(it);
            free(headers_str);
            return NULL;
        }

        strapp(&headers_str, current->key);
        strapp(&headers_str, ":");
        strapp(&headers_str, current->value);
        strapp(&headers_str, ";");
    }

    if (strsize(headers_str) > HEADER_STRING_LEN)
    {
        free(it);
        free(headers_str);
        return NULL;
    }

    free(it);
    return headers_str;
}
