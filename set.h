#ifndef SET_H
#define SET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "linked_list.h"

typedef struct set *SET;

struct set {
    LINKED_LIST *items;
    size_t size;
};

SET new_set(void);
void set_add(SET set, STRING_POINTER data);
void set_remove(SET set, STRING_POINTER data);
STRING_POINTER set_search(SET set, STRING_POINTER data);
void print_set(SET set);
size_t djb33x_hash(const char *str);
STRING_POINTER new_string_list_item(const char *str);

#endif // SET_H