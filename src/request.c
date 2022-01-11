#include "letschat/request.h"
#include <stdlib.h>
#include <string.h>

#define IS_LONGER(x, MAX) (strlen(x) > MAX)
#define IS_NULL(x) (x == NULL)

#define HEADER_STRING_LEN (HEADER_FIELD_MAXLEN * 2 + 2) * HEADERS_MAXCOUNT
#define REQUEST_STRING_MAXLEN (\
    (COMMAND_MAXLEN + 1) +\
    (USERNAME_MAXLEN + 1) +\
    (CHANNEL_MAXLEN + 1) +\
    (HEADER_STRING_LEN + 2) +\
    (MESSAGE_MAXLEN + 1)\
)

static char* command_serialize(const command_t command)
{
    switch (command)
    {
    case CONNECT:
        return "CONNECT";
    case DISCONNECT:
        return "DISCONNECT";
    case SEND:
        return "SEND";
    case BROADCAST:
        return "BROADCAST";
    default:
        return NULL;
    }
}

static char* serialize(const request_t* request)
{
    char* request_str = calloc(REQUEST_STRING_MAXLEN, sizeof *request_str);
    if (IS_NULL(request_str))
    {
        return NULL;
    }

    strcat(request_str, command_serialize(request->command));
    strcat(request_str, " ");

    strcat(request_str, request->username);
    strcat(request_str, "@");
    strcat(request_str, request->channel);
    strcat(request_str, " [");

    char* headers_str = headers_serialize(request->headers);
    if (IS_NULL(headers_str))
    {
        free(request_str);
        return NULL;
    }

    strcat(request_str, headers_str);
    strcat(request_str, "] ");

    strcat(request_str, request->message);

    char* new_request = realloc(request_str, strlen(request_str) + 1);
    if (IS_NULL(new_request))
    {
        free(request_str);
        return NULL;
    }

    return new_request;
}

static command_t command_parse(const char* raw_command)
{
    if (strcasecmp(raw_command, "CONNECT") == 0)
    {
        return CONNECT;
    }
    else if (strcasecmp(raw_command, "DISCONNECT") == 0)
    {
        return DISCONNECT;
    }
    else if (strcasecmp(raw_command, "SEND") == 0)
    {
        return SEND;
    }
    else if (strcasecmp(raw_command, "BROADCAST") == 0)
    {
        return BROADCAST;
    }
    else
    {
        return UNKNOWN;
    }
}

request_t* request_parse(const char* raw_request)
{
    request_t* request = malloc(sizeof *request);
    request->__raw = raw_request;
    request->serialize = serialize;

    char* src = strdup(raw_request);

    char* command = strtok_r(src, " ", &src);
    if (IS_NULL(command))
    {
        request_free(request);
        free(src);
        return NULL;
    }

    char* username = strtok_r(src, "@", &src);
    if (IS_NULL(username) || IS_LONGER(username, USERNAME_MAXLEN))
    {
        request_free(request);
        free(src);
        return NULL;
    }

    char* channel = strtok_r(src, " ", &src);
    if (IS_NULL(channel) || IS_LONGER(channel, CHANNEL_MAXLEN))
    {
        request_free(request);
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
            request_free(request);
            free(src);
            return NULL;
        }

        request->headers = headers;
    } else src++;

    src++;

    char* message = strtok_r(src, "\0", &src);
    if (IS_NULL(message) || IS_LONGER(message, MESSAGE_MAXLEN))
    {
        request_free(request);
        free(src);
        return NULL;
    }

    request->command = command_parse(command);
    request->username = username;
    request->channel = channel;
    request->message = message;

    return request;
}

void request_free(request_t* request)
{
    if (request == NULL)
    {
        return;
    }

    if (request->headers != NULL)
    {
        hashtable_free(request->headers);
    }

    if (request->username != NULL)
    {
        free(request->username);
    }

    if (request->channel != NULL)
    {
        free(request->channel);
    }

    if (request->message != NULL)
    {
        free(request->message);
    }

    free(request);
}
