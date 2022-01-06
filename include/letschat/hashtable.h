#ifndef __HASHTABLE__
#define __HASHTABLE__

#ifndef __PRIVATE_MODIFIER__
#   define __PRIVATE_MODIFIER__(x) __##x
#   define private(x) __PRIVATE_MODIFIER__(x)
#endif

#define HASHTABLE_STARTLEN 16

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

typedef struct entry
{
    const char* key;
    char* value;
} entry_t;

typedef struct hashtable
{
    // * PUBLIC
    uint32_t size;

    // * PRIVATES
    entry_t** private(entries);
    uint32_t private(capacity);

    // * METHODS
    /**
     * @brief Finds the entry with the given key in the hashtable.
     * @param table The table where to search in.
     * @param key The key to look for.
     * @return entry_t* The entry object.
     */
    entry_t* (*get)(struct hashtable* table, const char* key);
    /**
     * @brief Adds a new entry in the hashtable, or updates the value if exists.
     * @param table The table where to set the entry in.
     * @param key The key of the entry.
     * @param value The new value of the entry.
     * @return true if the entry has been set/updated.
     */
    bool (*set)(struct hashtable* table, const char* key, char* value);
} hashtable_t;


/**
 * @brief Create a new hashtable object.
 * 
 * @return hashtable_t* The new hashtable.
 */
hashtable_t* hashtable_new();

/**
 * @brief Deletes the hashtable and all its entries.
 * 
 * @param table The hashtable to delete.
 */
void hashtable_free(hashtable_t* table);

#ifdef __cplusplus
}
#endif

#endif // __HASHTABLE__
