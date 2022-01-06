#ifndef __HEADERS__
#define __HEADERS__

#include "hashtable.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef hashtable_t* headers_t;
typedef entry_t* header_t;

#define HEADERS_MAXCOUNT 32     // ? 32 chars = 32  B (256 bits)
#define HEADER_FIELD_MAXLEN 32  // ? 32 chars = 32  B (256 bits)

/**
 * @brief Get a raw string of a headers list and parse into a header hashtable.
 * 
 * @param raw_headers The string to parse
 * @return headers_t The parsed hashtable
 */
headers_t headers_parse(const char* raw_headers);

/**
 * @brief Get a headers hashtable and serialize it into a raw headers list string.
 * 
 * @param headers The hashtable to serialize
 * @return char* The serialized headers list string
 */
char* headers_serialize(headers_t headers);

#ifdef __cplusplus
}
#endif

#endif // __HEADERS__
