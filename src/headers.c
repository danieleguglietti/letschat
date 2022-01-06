#include "letschat/headers.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define IS_LONGER(x) (strlen(x) > HEADER_FIELD_MAXLEN)
#define NOT_NULL(x) (x != NULL)


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

        if (NOT_NULL(key) || NOT_NULL(value) || IS_LONGER(key) || IS_LONGER(value))
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
    return NULL;
}
