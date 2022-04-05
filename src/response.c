#include "letschat/response.h"
#include <stdlib.h>
#include <stdio.h>

#define IS_LONGER(x, MAX) (strsize(x) > MAX)
#define IS_NULL(x) (x == NULL)
#define NOT_NULL(x) (x != NULL)

#define HEADER_STRING_LEN (HEADER_FIELD_MAXLEN * 2 + 2) * HEADERS_MAXCOUNT
#define RESPONSE_STRING_MAXLEN (\
    (CODE_MAXLEN + 1) +\
    (HEADER_STRING_LEN + 2) +\
    (MESSAGE_MAXLEN + 1)\
)

static string_t code_serialize(const code_t code)
{
    string_t strcode = strinit(4, 0);
    sprintf(strcode, "%d", code);
    return strcode;
}

static string_t serialize(const response_t* response)
{
    string_t response_str = strinit(1, 0);
    if (IS_NULL(response_str))
    {
        return NULL;
    }

    strapp(&response_str, code_serialize(response->code));
    strapp(&response_str, " [");

    string_t headers_str = headers_serialize(response->headers);
    if (IS_NULL(headers_str))
    {
        free(response_str);
        return NULL;
    }

    strapp(&response_str, headers_str);
    strapp(&response_str, "] ");

    strapp(&response_str, response->message);

    return response_str;
}

static code_t code_parse(const string_t raw_code)
{
    switch(atoi(raw_code))
    {
    case CONNECTED:
        return CONNECTED;
    case DISCONNECTED:
        return DISCONNECTED;
    case FORWARDED:
        return FORWARDED;
    case RECEIVING:
        return RECEIVING;
    case DROPPED:
        return DROPPED;
    case UNKOWN_COMMAND:
        return UNKOWN_COMMAND;
    default:
        return BLOCKED;
    };
}

response_t* response_parse(const string_t raw_response)
{
    response_t* response = malloc(sizeof *response);
    response->__raw = raw_response;
    response->serialize = serialize;

    string_t src = dupstr(raw_response);
    string_t start = src;

    string_t code = strsplit(&src, ' ');
    if (IS_NULL(code))
    {
        response_free(response);
        free(start);
        return NULL;
    }

    src++;

    if (*src != ']')
    {
        string_t raw_header = strsplit(&src, ']');
        headers_t headers = headers_parse(raw_header);

        if (IS_NULL(headers))
        {
            response_free(response);
            free(start);
            return NULL;
        }

        response->headers = headers;
    } else src++;

    src++;

    string_t message = strsplit(&src, 0);
    if (IS_NULL(message) || IS_LONGER(message, MESSAGE_MAXLEN))
    {
        response_free(response);
        free(start);
        return NULL;
    }

    response->code = code_parse(code);
    response->message = message;

    return response;
}

void response_free(response_t* response)
{
    if (IS_NULL(response))
    {
        return;
    }

    if (NOT_NULL(response->headers))
    {
        hashtable_free(response->headers);
    }

    if (NOT_NULL(response->message))
    {
        free(response->message);
    }

    free(response);
}