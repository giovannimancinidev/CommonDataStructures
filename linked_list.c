#include "linked_list.h"

LINKED_LIST new_linked_list(void)
{
    LINKED_LIST list = malloc(sizeof(struct linked_list));
    if (!list) {
        fprintf(stderr, "Error: Unable to allocate memory for new list.\n");
        exit(1);
    }
    list->head = NULL;
    return list;
}

void list_insert(LINKED_LIST list, STRING_POINTER data)
{
    LIST_ITEM new_item = malloc(sizeof(struct linked_list_item));
    if (!new_item) {
        fprintf(stderr, "Error: Unable to allocate memory for new list item.\n");
        exit(1);
    }
    new_item->data = data;
    new_item->next = list->head;
    list->head = new_item;
}

void list_remove(LINKED_LIST list, STRING_POINTER data)
{
    LIST_ITEM current = list->head;
    LIST_ITEM prev = NULL;
    while (current) {
        if (strcmp(current->data->content, data->content) == 0) {
            if (prev) {
                prev->next = current->next;
            } else {
                list->head = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

LIST_ITEM list_search(LINKED_LIST list, STRING_POINTER data)
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

void print_list(LINKED_LIST list)
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
    LINKED_LIST list = new_linked_list();

    STRING_POINTER data1 = new_string_list_item("ORANGE");
    STRING_POINTER data2 = new_string_list_item("PINEAPPLE");
    STRING_POINTER data3 = new_string_list_item("GRAPE");
    STRING_POINTER data4 = new_string_list_item("KIWI");
    STRING_POINTER data5 = new_string_list_item("LEMON");

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