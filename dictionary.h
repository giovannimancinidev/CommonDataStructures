#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct dictionary_item *ITEM;
typedef struct dictionary *DICTIONARY;
typedef struct string_pointer *STRING_POINTER;
typedef void *VALUE;

struct dictionary_item {
    STRING_POINTER key;
    VALUE value;
    int index;
};

struct dictionary {
    ITEM *items;
    size_t hashmapSize;
    int collisionAmount;
};

struct string_pointer {
    char *content;
};

DICTIONARY new_dictionary(const size_t hashmapSize);
int dictionary_calculate_index(DICTIONARY dictionary, STRING_POINTER key);
ITEM dictionary_insert(DICTIONARY dictionary, STRING_POINTER key, VALUE value);
void dictionary_print(DICTIONARY dictionary);
void list_print(STRING_POINTER key);
VALUE get_dictionary_value(DICTIONARY dictionary, ITEM item);
void remove_item_in_dictionary(DICTIONARY dictionary, ITEM item);
void resize_dictionary(DICTIONARY dictionary);
STRING_POINTER new_string_list_item(const char *str);
size_t djb33x_hash(const char *str);
void insert_in_dictionary(DICTIONARY dictionary, STRING_POINTER key, VALUE value);
void search_in_dictionary(DICTIONARY dictionary, ITEM item, int index);

#endif // DICTIONARY_H