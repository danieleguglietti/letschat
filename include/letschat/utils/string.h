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

/**
 * @brief Copy a givven number of character from a string into another.
 *  The destination string must be large enough to hold the source string.
 * 
 * @param src The string to copy.
 * @param dest The destination string.
 * @param size The amounte of characters to copy.
 */
void strncopy(const string_t src, string_t dest, const uint64_t size);

/**
 * @brief Get the substring from a string.
 * 
 * @param str The string to get the substring from.
 * @param start The index to start the substring from.
 * @return string_t The substring.
 */
string_t substr(const string_t str, const uint64_t start);

/**
 * @brief Get the substring of a givven number of charaters from a string.
 * 
 * @param str The string to get the substring from.
 * @param start The index to start the substring from.
 * @param size The number of characters to get.
 * @return string_t The substring.
 */
string_t subnstr(const string_t str, const uint64_t start, const uint64_t size);

/**
 * @brief Duplicate a string.
 * 
 * @param str The string to duplicate.
 * @return string_t The new string.
 */
string_t dupstr(const string_t str);

/**
 * @brief Splits a string when finds the first occurency of the delimeter character.
 * 
 * @param str The string to split.
 * @param delim The delimeter character.
 * @return string_t The result.
 */
string_t strsplit(string_t str, const char delim);

__END_DECLS


#endif // __STRING__