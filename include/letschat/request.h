#ifndef __REQUEST__
#define __REQUEST__

#ifndef __PRIVATE_MODIFIER__
#   define __PRIVATE_MODIFIER__(x) __##x
#   define private(x) __PRIVATE_MODIFIER__(x)
#endif

#ifndef __MESSAGE_FIELDS_MAXLEN__
#define __MESSAGE_FIELDS_MAXLEN__
#   define USERNAME_MAXLEN  16      // ? 16   chars = 16  B (128  bits)
#   define CHANNEL_MAXLEN   32      // ? 32   chars = 32  B (256  bits)
#   define MESSAGE_MAXLEN   1024    // ? 1024 chars = 1  MB (8192 bits)
#endif

#include "headers.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum command
{
    CONNECT,
    DISCONNECT,
    SEND,
    BROADCAST,
    UNKOWN = -1
} command_t;

typedef struct request
{
    // * PUBLICS
    command_t command;
    headers_t headers;
    char* username;
    char* channel;
    char* message;

    // * PRIVATES
    const char* private(raw);

    // * METHODS
    /**
     * @brief Serialize a request object into a string.
     * @param request The object to serilized.
     * @return char* The serilized string.
     */
    char* (*serialize)(const struct request* request);
} request_t;

/**
 * @brief Parse the raw requst string into a request object
 * 
 * @param raw_request The raw request message.
 * @return request_t* The request object.
 */
request_t* request_parse(const char* raw_request);

#ifdef __cplusplus
}
#endif

#endif // __REQUEST__
