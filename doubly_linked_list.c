#include "doubly_linked_list.h"

DOUBLY_LINKED_LIST new_doubly_linked_list(void)
{
    DOUBLY_LINKED_LIST list = malloc(sizeof(struct doubly_linked_list));
    if (!list) {
        fprintf(stderr, "Error: Unable to allocate memory for new list.\n");
        exit(1);
    }
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void list_insert(DOUBLY_LINKED_LIST list, STRING_POINTER data)
{
    LIST_ITEM new_item = malloc(sizeof(struct doubly_linked_list_item));
    if (!new_item) {
        fprintf(stderr, "Error: Unable to allocate memory for new list item.\n");
        exit(1);
    }
    new_item->data = data;
    new_item->next = NULL;
    new_item->prev = list->tail;

    if (list->tail) {
        list->tail->next = new_item;
    }
    list->tail = new_item;

    if (!list->head) {
        list->head = new_item;
    }
}

void list_remove(DOUBLY_LINKED_LIST list, STRING_POINTER data)
{
    LIST_ITEM current = list->head;
    while (current) {
        if (strcmp(current->data->content, data->content) == 0) {
            if (current->prev) {
                current->prev->next = current->next;
            } else {
                list->head = current->next;
            }
            if (current->next) {
                current->next->prev = current->prev;
            } else {
                list->tail = current->prev;
            }
            free(current);
            return;
        }
        current = current->next;
    }
}

LIST_ITEM list_search(DOUBLY_LINKED_LIST list, STRING_POINTER data)
{
    LIST_ITEM current = list->head;
    while (current) {
        if (strcmp(current->data->content, data->content) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void print_list(DOUBLY_LINKED_LIST list)
{
    LIST_ITEM current = list->head;
    while (current) {
        printf("Key: %s\n", current->data->content);
        current = current->next;
    }
}

STRING_POINTER new_string_list_item(const char *str)
{
    STRING_POINTER sp = malloc(sizeof(struct string_pointer));
    sp->content = strdup(str);
    return sp;
}

int main(void)
{
    DOUBLY_LINKED_LIST list = new_doubly_linked_list();

    STRING_POINTER data1 = new_string_list_item("APPLE");
    STRING_POINTER data2 = new_string_list_item("BANANA");
    STRING_POINTER data3 = new_string_list_item("CHERRY");
    STRING_POINTER data4 = new_string_list_item("DATE");
    STRING_POINTER data5 = new_string_list_item("ELDERBERRY");

    printf("+++ ADDING ITEMS TO LIST +++\n");

    list_insert(list, data1);
    list_insert(list, data2);
    list_insert(list, data3);
    list_insert(list, data4);
    list_insert(list, data5);

    print_list(list);

    printf("\n");

    printf("+++ REMOVING ITEM FROM LIST +++\n");

    list_remove(list, data3);
    print_list(list);

    printf("\n");

    printf("+++ SEARCHING IN LIST +++\n");

    LIST_ITEM item = list_search(list, data2);
    if (item != NULL)
    {
        printf("Found item: %s\n", item->data->content);
    }
    else
    {
        printf("Item not found\n");
    }

    return 0;
}