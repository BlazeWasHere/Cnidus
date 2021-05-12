//          Copyright Blaze 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

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

/* search for the index of a key, returns -1 on failure */
int dict_find_index(dict_t dict, const char *key);

/* search for the value of a key, returns NULL on failure */
callback_t dict_find(dict_t dict, const char *key);

/* add the value with the specified key to the dict  */
void dict_add(dict_t dict, const char *key, callback_t value);

/* create and return a new dict */
dict_t dict_new(void);

/* remove all alloc'd memory, should be called when cleaning up memory */
void dict_free(dict_t dict);
