/**
 * based off: https://stackoverflow.com/a/16129177
 */

#pragma once

#include "server.h"

typedef void (*callback_t)(context*);

typedef struct dict_entry_s {
    char *key;          /* key, which should be our routes + method */
    callback_t value;   /* our callback fn */
} dict_entry_s;

typedef struct dict_s {
    uint32_t len;
    uint32_t cap;
    dict_entry_s *entry;
} dict_s, *dict_t;

int dict_find_index(dict_t dict, const char *key);
callback_t dict_find(dict_t dict, const char *key);
void dict_add(dict_t dict, const char *key, callback_t value);
dict_t dict_new(void);
void dict_free(dict_t dict);
