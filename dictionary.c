#include "dictionary.h"

DICTIONARY new_dictionary(const size_t hashmapSize)
{
    if (!hashmapSize)
    {
        fprintf(stderr, "Fatal Error: Unable to create a table with size 0!\n");
        return NULL;
    }

    DICTIONARY dictionary = malloc(sizeof(struct dictionary));

    if (!dictionary)
    {
        fprintf(stderr, "Fatal Error: Insufficient memory for dictionary allocation!\n");
        return NULL;
    }

    dictionary->hashmapSize = hashmapSize;
    dictionary->items = calloc(dictionary->hashmapSize, sizeof(ITEM));

    if (!dictionary->items)
    {
        free(dictionary);
        fprintf(stderr, "Fatal Error: Insufficient memory for items allocation!\n");
        return NULL;
    }

    dictionary->collisionAmount = 0;

    return dictionary;
}

int dictionary_calculate_index(DICTIONARY dictionary, STRING_POINTER key)
{
    const size_t keyLen = strlen(key->content);

    if (!key->content || !keyLen)
    {
        return -1;
    }

    size_t hash = djb33x_hash(key->content);
    int index = hash % dictionary->hashmapSize;

    return index;
}

ITEM dictionary_insert(DICTIONARY dictionary, STRING_POINTER key, VALUE value)
{
    int index = dictionary_calculate_index(dictionary, key);
    if (index < 0) {
        fprintf(stderr, "Error: Invalid key for dictionary insertion.\n");
        return NULL;
    }

    ITEM item = malloc(sizeof(struct dictionary_item));
    if (!item) {
        fprintf(stderr, "Error: Insufficient memory for dictionary item.\n");
        return NULL;
    }

    item->key = key;
    item->value = value;
    item->index = index;

    if (dictionary->items[index] != NULL) {
        dictionary->collisionAmount++;
    }

    dictionary->items[index] = item;

    return item;
}

void dictionary_print(DICTIONARY dictionary)
{
    for (size_t i = 0; i < dictionary->hashmapSize; ++i)
    {
        if (dictionary->items[i] != NULL)
        {
            printf("Index %zu: ", i);
            list_print(dictionary->items[i]->key);
        }
    }
}

void list_print(STRING_POINTER key)
{
    printf("Key: %s\n", key->content);
}

VALUE get_dictionary_value(DICTIONARY dictionary, ITEM item)
{
    if (item == NULL) return NULL;
    return item->value;
}

void remove_item_in_dictionary(DICTIONARY dictionary, ITEM item)
{
    if (item == NULL) return;
    int index = item->index;
    free(dictionary->items[index]);
    dictionary->items[index] = NULL;
}

void resize_dictionary(DICTIONARY dictionary)
{
    size_t oldHashmapSize = dictionary->hashmapSize;
    dictionary->hashmapSize = (dictionary->hashmapSize * 2);

    ITEM* newItems = calloc(dictionary->hashmapSize, sizeof(ITEM));

    if (!newItems)
    {
        free(dictionary);
        fprintf(stderr, "Fatal Error: Insufficient memory for new items allocation!\n");
    }

    for (size_t i = 0; i < oldHashmapSize; ++i)
    {
        if (dictionary->items[i])
        {
            size_t newIndex = dictionary->items[i]->index % dictionary->hashmapSize;
            newItems[newIndex] = dictionary->items[i];
        }
    }

    free(dictionary->items);
    dictionary->items = newItems;
}

size_t djb33x_hash(const char *str)
{
    size_t hash = 5381;
    int c;

    while ((c = *str++))
    {
        hash = ((hash << 5) + hash) ^ c;
    }

    return hash;
}

void insert_in_dictionary(DICTIONARY dictionary, STRING_POINTER key, VALUE value)
{
    dictionary_insert(dictionary, key, value);
}

void search_in_dictionary(DICTIONARY dictionary, ITEM item, int index)
{
    if (item == NULL)
    {
        printf("Item not found\n");
        return;
    }

    printf("Found item at index %d with key: %s\n", index, item->key->content);
}

STRING_POINTER new_string_list_item(const char *str)
{
    STRING_POINTER sp = malloc(sizeof(struct string_pointer));
    sp->content = strdup(str);
    return sp;
}

int main(void)
{
    DICTIONARY dictionary = new_dictionary(3);

    STRING_POINTER key1 = new_string_list_item("XBOX");
    STRING_POINTER key2 = new_string_list_item("ITALY");
    STRING_POINTER key3 = new_string_list_item("WARRIOR");
    STRING_POINTER key4 = new_string_list_item("PLAYSTATION");
    STRING_POINTER key5 = new_string_list_item("BANKS");
    STRING_POINTER key6 = new_string_list_item("NINTENDO");
    STRING_POINTER key10 = new_string_list_item("SONY");

    printf("+++ INITIATING DICTIONARY POPULATION +++\n");

    ITEM item1 = dictionary_insert(dictionary, key1, (VALUE)"MICROSOFT");
    ITEM item2 = dictionary_insert(dictionary, key2, (VALUE)123456);
    ITEM item3 = dictionary_insert(dictionary, key3, (VALUE)'H');
    ITEM item4 = dictionary_insert(dictionary, key4, (VALUE)-123);
    ITEM item5 = dictionary_insert(dictionary, key5, (VALUE)-99999);
    ITEM item6 = dictionary_insert(dictionary, key6, (VALUE)true);
    ITEM item7 = NULL;
    ITEM item10 = NULL;

    dictionary_print(dictionary);

    printf("\n");

    printf("+++ RESIZING DICTIONARY +++\n");

    resize_dictionary(dictionary);
    dictionary_print(dictionary);

    printf("\n");

    printf("+++ EXECUTING ERROR TESTS +++\n");

    insert_in_dictionary(dictionary, key3, (VALUE)567);
    VALUE valueTest1 = get_dictionary_value(dictionary, item7);
    remove_item_in_dictionary(dictionary, item10);

    printf("\n");

    printf("+++ RUNNING SEARCH TESTS +++\n");

    search_in_dictionary(dictionary, item2, -1);
    search_in_dictionary(dictionary, item4, -1);

    printf("\n");

    printf("+++ VALIDATING RETRIEVED VALUES +++\n");

    printf("Dictionary Key: %s, Stored Value: %s\n", item1->key->content, *(char**)get_dictionary_value(dictionary, item1));
    printf("Dictionary Key: %s, Stored Value: %d\n", item2->key->content, *(int*)get_dictionary_value(dictionary, item2));

    printf("\n");

    printf("+++ REMOVING ITEMS FROM DICTIONARY +++\n");

    remove_item_in_dictionary(dictionary, item4);
    remove_item_in_dictionary(dictionary, item6);

    return 0;
}