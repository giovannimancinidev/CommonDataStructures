#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct doubly_linked_list_item *LIST_ITEM;
typedef struct doubly_linked_list *DOUBLY_LINKED_LIST;
typedef struct string_pointer *STRING_POINTER;

struct doubly_linked_list_item {
    STRING_POINTER data;
    LIST_ITEM next;
    LIST_ITEM prev;
};

struct doubly_linked_list {
    LIST_ITEM head;
    LIST_ITEM tail;
};

struct string_pointer {
    char *content;
};

DOUBLY_LINKED_LIST new_doubly_linked_list(void);
void list_insert(DOUBLY_LINKED_LIST list, STRING_POINTER data);
void list_remove(DOUBLY_LINKED_LIST list, STRING_POINTER data);
LIST_ITEM list_search(DOUBLY_LINKED_LIST list, STRING_POINTER data);
void print_list(DOUBLY_LINKED_LIST list);
STRING_POINTER new_string_list_item(const char *str);

#endif // DOUBLY_LINKED_LIST_H