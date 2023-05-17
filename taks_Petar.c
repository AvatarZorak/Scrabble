#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>

struct node
{
    char value;
    struct darray* children;
    bool is_word;
};

struct darray
{
    struct node** nodes;
    int count;
    int capacity;
};

struct darray* create_darray(int capacity) {
    struct darray* new_arr = calloc(1, sizeof(struct darray));

    new_arr->nodes = calloc(capacity, sizeof(struct node*));
    new_arr->capacity = capacity;
    new_arr->count = 0;

    return new_arr;
}

struct node* create_node(char value)
{
    struct node* new_node = calloc(1, sizeof(struct node));

    new_node->value = value;
    new_node->children = create_darray(4);
    new_node->is_word = false;

    return new_node;
}

struct node* darray_contains(struct darray* arr, char letter)
{
    for(int i = 0; i < arr->count; i++)
    {
        if(arr->nodes[i]->value == letter)
        {
            return arr->nodes[i];
        }
    }

    return NULL;
}

void darray_add(struct darray* arr, char letter)
{
    arr->nodes[arr->count++] = create_node(letter);
}

void insert_word(struct node* root, char* word, int current_index)
{
    struct node* contains = darray_contains(root->children, word[current_index]);

    if(contains)
    {
        insert_word(contains, word, current_index + 1);
    } else
    {
        struct node* iterator = root;

        for(int i = current_index; i < strlen(word); i++)
        {
            darray_add(iterator->children, word[i]);

            iterator = iterator->children->nodes[iterator->children->count - 1];
        }

        iterator->is_word = true;

        return;
    }

    if(current_index == strlen(word) - 1)
    {
        root->is_word = true;

        return;
    }
}

void print_trie(struct node* root) {

    printf("%c\n", root->value);

    for(int i = 0; i < root->children->count; i++) {
        print_trie(root->children->nodes[i]);
    }
}

int words_in_dict(FILE *d_file) //getting the lines from the dictionary - getting the words
{
    int lines = 0;
    int ch;

    while ((ch = fgetc(d_file)) != EOF)
    {
        if (ch == '\n')
        {
            lines++;
        }
    }
    return lines + 1;

}

char** create_dictionary(char** dictionary, int size, FILE *d_file)
{
    char line[15];

    fseek(d_file, 0, SEEK_SET);

    dictionary = malloc(size * sizeof(char*));

    for (int i = 0; fgets(line, 15, d_file) != NULL; i++)
    {
        dictionary[i] = strdup(line);
    }

    return dictionary;

}

void printDictionary(char** dictionary, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("Word number %d: %s\n", i, dictionary[i]);
    }
}

int main() {

    FILE *dict_file;

    dict_file = fopen("dictionary.txt", "r");

    if (dict_file == NULL)
    {
        printf("Unable to open the file.\n");
        return 0;
    }

    char** dictionary;
    int size_dict = words_in_dict(dict_file);

    printf("Lines : %d \n", size_dict);

    dictionary = create_dictionary(dictionary, size_dict, dict_file);

    printDictionary(dictionary, size_dict);

    struct node* root = create_node(' ');

    insert_word(root, "alex", 0);
    insert_word(root, "albatroz", 0);

    print_trie(root);

    fclose(dict_file);

    return 0;
}
