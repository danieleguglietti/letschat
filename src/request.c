#include "letschat/request.h"
#include <stdlib.h>
#include <string.h>

#define IS_LONGER(x, MAX) (strlen(x) > MAX)
#define IS_NULL(x) (x == NULL)

static char* serialize(const request_t* request)
{
    return NULL;
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

    request->username = username;
    request->channel = channel;
    request->message = message;
    request->message = message;

    return request;
}

void request_free(request_t* request)
{
    hashtable_free(request->headers);
    free(request->username);
    free(request->channel);
    free(request->message);
    free(request);
}
