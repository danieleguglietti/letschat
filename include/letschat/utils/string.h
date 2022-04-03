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
 * @brief Append a string to the source.
 * 
 * @param source Pointer to the string to append in.
 * @param str The string to append.
 * @return string_t The new string.
 */
string_t strapp(string_t* source, const string_t str);

/**
 * @brief Finds the first occurrence of a character in a string.
 * 
 * @param str The string to search in.
 * @param ch The character to search for.
 * @return int64_t The index of the character in the string.
 */
int64_t strfind(const string_t str, const char ch);

/**
 * @brief Copy a string into another.
 *  The destination string must be large enough to hold the source string.
 * 
 * @param src The string to copy.
 * @param dest The destination string.
 */
void strcopy(const string_t src, string_t dest);

__END_DECLS


#endif // __STRING__