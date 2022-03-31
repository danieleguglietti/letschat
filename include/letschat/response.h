#ifndef __RESPONSE__
#define __RESPONSE__

#ifndef __PRIVATE_MODIFIER__
#   define __PRIVATE_MODIFIER__(x) __##x
#   define private(x) __PRIVATE_MODIFIER__(x)
#endif

#ifndef __RESPONSE_MESSAGE_FIELDS_MAXLEN__
#define __RESPONSE_MESSAGE_FIELDS_MAXLEN__
#   define CODE_MAXLEN      32      // ? 32   chars = 32  B (256  bits)
#   ifndef MESSAGE_MAXLEN
#      define MESSAGE_MAXLEN   1024    // ? 1024 chars = 1  MB (8192 bits)
#   endif
#endif

#include "headers.h"

__BEGIN_DECLS

typedef enum code
{
    // * SUCCESS
    CONNECTED = 200,
#define CONNECTED CONNECTED
    DISCONNECTED,
#define DISCONNECTED DISCONNECTED
    FORWARDED,
#define FORWARDED FORWARDED
    RECEIVING,
#define RECEIVING RECEIVING
    DROPPED = 400,
    // * ERROR
#define DROPPED DROPPED
    UNKOWN_COMMAND,
#define UNKOWN_COMMAND UNKOWN_COMMAND
    BLOCKED,
#define BLOCKED BLOCKED
} code_t;

typedef struct response
{
    // * PUBLICS
    /**
     * @brief The message code.
     */
    code_t code;
    /**
     * @brief The hashtable containing the message headers.
     */
    headers_t headers;
    /**
     * @brief The message body.
     */
    char* message;

    // ! PRIVATES
    const char* private(raw);

    // ? METHODS
    /**
     * @brief Serialize a response object into a string.
     * @param response The object to serilized.
     * @return char* The serilized string.
     */
    char* (*serialize)(const struct response* response);
} response_t;

/**
 * @brief Parse the raw requst string into a response object
 * 
 * @param raw_response The raw response message.
 * @return response_t* The response object.
 */
response_t* response_parse(const char* raw_response);

/**
 * @brief Frees memory allocated bye the response object.
 * 
 * @param response The object to free
 */
void response_free(response_t* response);

__END_DECLS

#endif // __RESPONSE__
