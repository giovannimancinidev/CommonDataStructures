#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct linked_list_item *LIST_ITEM;
typedef struct linked_list *LINKED_LIST;
typedef struct string_pointer *STRING_POINTER;

struct linked_list_item {
    STRING_POINTER data;
    LIST_ITEM next;
};

struct linked_list {
    LIST_ITEM head;
};

struct string_pointer {
    char *content;
};

LINKED_LIST new_linked_list(void);
void list_insert(LINKED_LIST list, STRING_POINTER data);
void list_remove(LINKED_LIST list, STRING_POINTER data);
LIST_ITEM list_search(LINKED_LIST list, STRING_POINTER data);
void print_list(LINKED_LIST list);
STRING_POINTER new_string_list_item(const char *str);

#endif // LINKED_LIST_H