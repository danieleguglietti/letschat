#include "letschat/hashtable.h"
#include <stdlib.h>
#include <string.h>

#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

static uint64_t hash(const char* key)
{
    uint64_t hash = FNV_OFFSET;

    for (const char* ch = key; *ch != '\0'; ch++)
    {
        hash ^= *ch;
        hash *= FNV_PRIME;
    }

    return hash;
}

#define GET_INDEX(key, table) (hash(key) & (table->__capacity - 1))

static entry_t* get(hashtable_t* table, const char* key)
{
    uint32_t index = (uint32_t) GET_INDEX(key, table);
    entry_t** entries = table->__entries;

    while (entries[index] != NULL)
    {
        entry_t* entry = entries[index];

        if (strcmp(entry->key, key) == 0)
            return entry;

        index++;

        if (index == table->__capacity)
        {
            index = 0;
        }
    }

    return NULL;
}

static entry_t* entry_new(const char* key, char* value)
{
    entry_t* entry = malloc(sizeof *entry);

    if (entry == NULL)
    {
        return NULL;
    }

    entry->key = key;
    entry->value = value;

    return entry;
}

static void set_entry(entry_t** entries, hashtable_t* table, const char* key, char* value)
{
    uint32_t index = (uint32_t) GET_INDEX(key, table);

    while (entries[index] != NULL)
    {
        entry_t* entry = entries[index];

        if (strcmp(entry->key, key) == 0)
        {
            entry->value = value;
            return;
        }

        index++;

        if (index == table->__capacity)
        {
            index = 0;
        }
    }

    entry_t* entry = entry_new(key, value);

    if (entry == NULL)
    {
        return;
    }

    entries[index] = entry;

    table->size++;
}

static void resize(hashtable_t* table)
{
    uint32_t new_capacity = table->__capacity * 2;
    entry_t** new_entries = calloc(new_capacity, sizeof *new_entries);

    for (uint32_t i = 0; i < table->__capacity; i++)
    {
        entry_t* entry = table->__entries[i];

        if (entry != NULL)
            set_entry(new_entries, table, entry->key, entry->value);
    }

    free(table->__entries);
    table->__entries = new_entries;

    table->__capacity = new_capacity;
}

static bool set(hashtable_t* table, const char* key, char* value)
{
    if (value == NULL)
        return false;

    if (table->size == table->__capacity * 0.5)
        resize(table);

    set_entry(table->__entries, table, key, value);

    return true;
}

static bool has_next(hashtable_it* iterator)
{
    hashtable_t* table = iterator->__table;

    while (iterator->__index < table->__capacity)
    {
        entry_t* entry = table->__entries[iterator->__index];

        if (entry != NULL)
        {
            iterator->current = entry;
            return true;
        }

        iterator->__index++;
    }

    return false;
}

static hashtable_it* new_iterator(hashtable_t* table)
{
    hashtable_it* it = malloc(sizeof *it);

    if (it == NULL)
    {
        return NULL;
    }

    it->__table = table;
    it->__index = 0;
    it->current = NULL;

    it->next = has_next;

    return it;
}

hashtable_t* hashtable_new()
{
    hashtable_t* table = malloc(sizeof *table);

    if (table == NULL)
    {
        return NULL;
    }

    table->size = 0;
    table->__capacity = HASHTABLE_STARTLEN;

    table->__entries = calloc(table->__capacity, sizeof *table->__entries);

    if (table->__entries == NULL)
    {
        free(table);
        return NULL;
    }

    table->get = get;
    table->set = set;
    table->iterator = new_iterator;

    return table;
}

void hashtable_free(hashtable_t* table)
{
    for (uint32_t i = 0; i < table->__capacity; i++)
    {
        entry_t* entry = table->__entries[i];

        if (entry != NULL)
            free(entry);
    }

    free(table->__entries);
    free(table);
}
