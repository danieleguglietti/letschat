#ifndef __STRING__
#define __STRING__

#include <stdint.h>

__BEGIN_DECLS

typedef char* string_t;

/**
 * @brief Calculate the size of a null-terminated string.
 * 
 * @param str The string to calculate the size of.
 * @return uint64_t The string size.
 */
uint64_t strsize(const string_t str);

/**
 * @brief Append a character to the string.
 * 
 * @param str The string to append the character to.
 * @param ch The character to append.
 */
void strapp(string_t str, const char ch);

__END_DECLS


#endif // __STRING__