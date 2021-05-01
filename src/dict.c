//          Copyright Blaze 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "dict.h"

int dict_find_index(dict_t dict, const char *key) {
    for (uint32_t i = 0; i < dict->len; i++) {
        if (!strcmp((dict->entry[i].key), key)) {
            return i;
        }
    }
    return -1;
}

callback_t dict_find(dict_t dict, const char *key) {
    int idx = dict_find_index(dict, key);
    return idx == -1 ? NULL : dict->entry[idx].value;
}

void dict_add(dict_t dict, const char *key, callback_t value) {
   int idx = dict_find_index(dict, key);
   if (idx != -1) {
       dict->entry[idx].value = value;
       return;
   }
   if (dict->len == dict->cap) {
       dict->cap *= 2;
       dict->entry = realloc(dict->entry, dict->cap * sizeof(dict_entry_s));
   }
   dict->entry[dict->len].key = strdup(key);
   dict->entry[dict->len].value = value;
   dict->len++;
}

dict_t dict_new(void) {
    dict_s proto = {0, 10, malloc(10 * sizeof(dict_entry_s))};
    dict_t d = malloc(sizeof(dict_s));
    *d = proto;
    return d;
}

void dict_free(dict_t dict) {
    for (uint32_t i = 0; i < dict->len; i++) {
        free(dict->entry[i].key);
    }
    free(dict->entry);
    free(dict);
}