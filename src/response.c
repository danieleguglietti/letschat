#include "letschat/response.h"
#include <stdlib.h>
#include <string.h>

#define IS_LONGER(x, MAX) (strlen(x) > MAX)
#define IS_NULL(x) (x == NULL)
#define NOT_NULL(x) (x != NULL)

#define HEADER_STRING_LEN (HEADER_FIELD_MAXLEN * 2 + 2) * HEADERS_MAXCOUNT
#define RESPONSE_STRING_MAXLEN (\
    (CODE_MAXLEN + 1) +\
    (HEADER_STRING_LEN + 2) +\
    (MESSAGE_MAXLEN + 1)\
)

static char* code_serialize(const code_t code)
{
    switch (code)
    {
    case CONNECTED:
        return "CONNECTED";
    case DISCONNECTED:
        return "DISCONNECTED";
    case FORWARDED:
        return "FORWARDED";
    case RECEIVING:
        return "RECEIVING";
    case DROPPED:
        return "DROPPED";
    case UNKOWN_COMMAND:
        return "UNKOWN_COMMAND";
    case BLOCKED:
        return "BLOCKED";
    default:
        return NULL;
    }
}

static char* serialize(const response_t* response)
{
    char* response_str = calloc(RESPONSE_STRING_MAXLEN, sizeof *response_str);
    if (IS_NULL(response_str))
    {
        return NULL;
    }

    strcat(response_str, code_serialize(response->code));
    strcat(response_str, " [");

    char* headers_str = headers_serialize(response->headers);
    if (IS_NULL(headers_str))
    {
        free(response_str);
        return NULL;
    }

    strcat(response_str, headers_str);
    strcat(response_str, "] ");

    strcat(response_str, response->message);

    char* new_response = realloc(response_str, strlen(response_str) + 1);
    if (IS_NULL(new_response))
    {
        free(response_str);
        return NULL;
    }

    return new_response;
}

static code_t code_parse(const char* raw_code)
{
    if (strcasecmp(raw_code, "CONNECTED") == 0)
    {
        return CONNECTED;
    }
    else if (strcasecmp(raw_code, "DISCONNECTED") == 0)
    {
        return DISCONNECTED;
    }
    else if (strcasecmp(raw_code, "FORWARDED") == 0)
    {
        return FORWARDED;
    }
    else if (strcasecmp(raw_code, "RECEIVING") == 0)
    {
        return RECEIVING;
    }
    else if (strcasecmp(raw_code, "DROPPED") == 0)
    {
        return DROPPED;
    }
    else if (strcasecmp(raw_code, "UNKOWN_COMMAND") == 0)
    {
        return UNKOWN_COMMAND;
    }
    else
    {
        return BLOCKED;
    }
}

response_t* response_parse(const char* raw_response)
{
    response_t* response = malloc(sizeof *response);
    response->__raw = raw_response;
    response->serialize = serialize;

    char* src = strdup(raw_response);

    char* code = strtok_r(src, " ", &src);
    if (IS_NULL(code))
    {
        response_free(response);
        free(src);
        return NULL;
    }

    src++;

    if (*src != ']')
    {
        char* raw_header = strtok_r(src, "]", &src);
        headers_t headers = headers_parse(raw_header);

        if (IS_NULL(headers))
        {
            response_free(response);
            free(src);
            return NULL;
        }

        response->headers = headers;
    } else src++;

    src++;

    char* message = strtok_r(src, "\0", &src);
    if (IS_NULL(message) || IS_LONGER(message, MESSAGE_MAXLEN))
    {
        response_free(response);
        free(src);
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