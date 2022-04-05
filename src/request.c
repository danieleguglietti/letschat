#include "letschat/request.h"
#include <stdlib.h>

#define IS_LONGER(x, MAX) (strsize(x) > MAX)
#define IS_NULL(x) (x == NULL)
#define NOT_NULL(x) (x != NULL)

#define HEADER_STRING_LEN (HEADER_FIELD_MAXLEN * 2 + 2) * HEADERS_MAXCOUNT
#define REQUEST_STRING_MAXLEN (\
    (COMMAND_MAXLEN + 1) +\
    (USERNAME_MAXLEN + 1) +\
    (CHANNEL_MAXLEN + 1) +\
    (HEADER_STRING_LEN + 2) +\
    (MESSAGE_MAXLEN + 1)\
)

static string_t command_serialize(const command_t command)
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

static string_t serialize(const request_t* request)
{
    string_t request_str = strinit(1, 0);
    if (IS_NULL(request_str))
    {
        return NULL;
    }

    strapp(&request_str, command_serialize(request->command));
    strapp(&request_str, " ");

    strapp(&request_str, request->username);
    strapp(&request_str, "@");
    strapp(&request_str, request->channel);
    strapp(&request_str, " [");

    string_t headers_str = headers_serialize(request->headers);
    if (IS_NULL(headers_str))
    {
        free(request_str);
        return NULL;
    }

    strapp(&request_str, headers_str);
    strapp(&request_str, "] ");

    strapp(&request_str, request->message);

    return request_str;
}

static command_t command_parse(string_t raw_command)
{
    if (streq_nocase(raw_command, "CONNECT"))
    {
        return CONNECT;
    }
    else if (streq_nocase(raw_command, "DISCONNECT"))
    {
        return DISCONNECT;
    }
    else if (streq_nocase(raw_command, "SEND"))
    {
        return SEND;
    }
    else if (streq_nocase(raw_command, "BROADCAST"))
    {
        return BROADCAST;
    }
    else
    {
        return UNKNOWN;
    }
}

request_t* request_parse(string_t raw_request)
{
    request_t* request = malloc(sizeof *request);
    request->__raw = raw_request;
    request->serialize = serialize;

    string_t src = dupstr(raw_request);
    string_t start = src;

    string_t command = strsplit(&src, ' ');
    if (IS_NULL(command))
    {
        request_free(request);
        free(start);
        return NULL;
    }

    string_t username = strsplit(&src, '@');
    if (IS_NULL(username) || IS_LONGER(username, USERNAME_MAXLEN))
    {
        request_free(request);
        free(start);
        return NULL;
    }

    string_t channel = strsplit(&src, ' ');
    if (IS_NULL(channel) || IS_LONGER(channel, CHANNEL_MAXLEN))
    {
        request_free(request);
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
            request_free(request);
            free(start);
            return NULL;
        }

        request->headers = headers;
    } else src++;

    src++;

    string_t message = strsplit(&src, 0);
    if (IS_NULL(message) || IS_LONGER(message, MESSAGE_MAXLEN))
    {
        request_free(request);
        free(start);
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

    if (NOT_NULL(request->headers))
    {
        hashtable_free(request->headers);
    }

    if (NOT_NULL(request->username))
    {
        free(request->username);
    }

    if (NOT_NULL(request->channel))
    {
        free(request->channel);
    }

    if (NOT_NULL(request->message))
    {
        free(request->message);
    }

    free(request);
}
