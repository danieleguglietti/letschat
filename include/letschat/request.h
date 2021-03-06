#ifndef __REQUEST__
#define __REQUEST__

#ifndef __PRIVATE_MODIFIER__
#   define __PRIVATE_MODIFIER__(x) __##x
#   define PRIVATE(x) __PRIVATE_MODIFIER__(x)
#endif

#ifndef __REQUEST_MESSAGE_FIELDS_MAXLEN__
#define __REQUEST_MESSAGE_FIELDS_MAXLEN__
#   define COMMAND_MAXLEN   32      // ? 32   chars = 32  B (256  bits)
#   define USERNAME_MAXLEN  16      // ? 16   chars = 16  B (128  bits)
#   define CHANNEL_MAXLEN   32      // ? 32   chars = 32  B (256  bits)
#   ifndef MESSAGE_MAXLEN
#      define MESSAGE_MAXLEN   1024    // ? 1024 chars = 1  MB (8192 bits)
#   endif
#endif

#include "headers.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum command
{
    CONNECT,
#define CONNECT CONNECT
    DISCONNECT,
#define DISCONNECT DISCONNECT
    SEND,
#define SEND SEND
    BROADCAST,
#define BROADCAST BROADCAST
    UNKNOWN = -1
#define UNKNOWN UNKNOWN
} command_t;

typedef struct request
{
    // * PUBLICS
    /**
     * @brief The message command.
     */
    command_t command;
    /**
     * @brief The hashtable containing the message headers.
     */
    headers_t headers;
    /**
     * @brief The message sender username. 
     */
    string_t username;
    /**
     * @brief The message channel.
     */
    string_t channel;
    /**
     * @brief The message body.
     */
    string_t message;

    // ! PRIVATES
    string_t PRIVATE(raw);

    // ? METHODS
    /**
     * @brief Serialize a request object into a string.
     * @param request The object to serilized.
     * @return char* The serilized string.
     */
    string_t (*serialize)(const struct request* request);
} request_t;

/**
 * @brief Parse the raw requst string into a request object
 * 
 * @param raw_request The raw request message.
 * @return request_t* The request object.
 */
request_t* request_parse(string_t raw_request);

/**
 * @brief Frees memory allocated bye the request object.
 * 
 * @param request The object to free
 */
void request_free(request_t* request);

#ifdef __cplusplus
}
#endif

#endif // __REQUEST__
