#include "set.h"

SET new_set(void)
{
    SET set = malloc(sizeof(struct set));
    if (!set) {
        fprintf(stderr, "Error: Unable to allocate memory for new set.\n");
        exit(1);
    }
    set->size = 10; // Example size, adjust as needed
    set->items = calloc(set->size, sizeof(LINKED_LIST));
    return set;
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

void set_add(SET set, STRING_POINTER data)
{
    size_t index = djb33x_hash(data->content) % set->size;
    if (!set->items[index]) {
        set->items[index] = malloc(sizeof(struct linked_list));
        set->items[index]->head = NULL;
    }
    list_insert(set->items[index], data);
}

void set_remove(SET set, STRING_POINTER data)
{
    size_t index = djb33x_hash(data->content) % set->size;
    if (set->items[index]) {
        list_remove(set->items[index], data);
    }
}

STRING_POINTER set_search(SET set, STRING_POINTER data)
{
    size_t index = djb33x_hash(data->content) % set->size;
    if (set->items[index]) {
        LIST_ITEM item = list_search(set->items[index], data);
        if (item) {
            return item->data;
        }
    }
    return NULL;
}

void print_set(SET set)
{
    for (size_t i = 0; i < set->size; i++) {
        if (set->items[i]) {
            print_list(set->items[i]);
        }
    }
}

size_t djb33x_hash(const char *str)
{
    size_t hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) ^ c;
    }

    return hash;
}

STRING_POINTER new_string_list_item(const char *str)
{
    STRING_POINTER sp = malloc(sizeof(struct string_pointer));
    sp->content = _strdup(str); // Use _strdup instead of strdup
    return sp;
}

int main(void)
{
    SET set = new_set();

    STRING_POINTER data1 = new_string_list_item("DOG");
    STRING_POINTER data2 = new_string_list_item("CAT");
    STRING_POINTER data3 = new_string_list_item("BIRD");
    STRING_POINTER data4 = new_string_list_item("FISH");
    STRING_POINTER data5 = new_string_list_item("HORSE");

    printf("+++ ADDING ITEMS TO SET +++\n");

    set_add(set, data1);
    set_add(set, data2);
    set_add(set, data3);
    set_add(set, data4);
    set_add(set, data5);

    print_set(set);

    printf("\n");

    printf("+++ REMOVING ITEM FROM SET +++\n");

    set_remove(set, data3);
    print_set(set);

    printf("\n");

    printf("+++ SEARCHING IN SET +++\n");

    STRING_POINTER item = set_search(set, data2);
    if (item != NULL)
    {
        printf("Found item: %s\n", item->content);
    }
    else
    {
        printf("Item not found\n");
    }

    return 0;
}