#include "letschat/headers.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define IS_LONGER(x) (strlen(x) > HEADER_FIELD_MAXLEN)
#define IS_NULL(x) (x == NULL)

#define HEADER_STRING_LEN (HEADER_FIELD_MAXLEN * 2 + 2) * HEADERS_MAXCOUNT

static char* strtrm(char* str) 
{
    size_t len = strlen(str);

    while(isspace(str[len - 1])) --len;
    while(*str && isspace(*str)) ++str, --len;

    return strndup(str, len);
}

headers_t headers_parse(const char* raw_headers)
{
    headers_t headers = hashtable_new();
    if (headers == NULL)
    {
        return NULL;
    }

    char* src = strdup(raw_headers), *ctx;

    char* header = strtok_r(src, ";", &ctx);

    while (header != NULL)
    {
        char* key = strtrm(strtok(header, ":"));
        char* value = strtrm(strtok(NULL, ";"));

        if (IS_NULL(key) || IS_NULL(value) || IS_LONGER(key) || IS_LONGER(value))
        {
            hashtable_free(headers);
            free(value);
            free(src);
            free(key);
            return NULL;
        }

        headers->set(headers, key, value);

        header = strtok_r(NULL, ";", &ctx);
    }

    if (headers->size > HEADERS_MAXCOUNT)
    {
        hashtable_free(headers);
        free(src);
        return NULL;
    }

    free(src);
    return headers;
}

char* headers_serialize(headers_t headers)
{
    char* headers_str = calloc(HEADER_STRING_LEN, sizeof *headers_str);
    if (headers_str == NULL)
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

        strcat(headers_str, current->key);
        strcat(headers_str, ":");
        strcat(headers_str, current->value);
        strcat(headers_str, ";");
    }

    if (strlen(headers_str) > HEADER_STRING_LEN)
    {
        free(it);
        free(headers_str);
        return NULL;
    }

    headers_str = realloc(headers_str, strlen(headers_str) + 1);
    if (headers_str == NULL) 
    {
        free(it);
        return NULL;
    }

    free(it);
    return headers_str;
}
