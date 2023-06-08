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

struct darray* create_darray(int capacity)
{
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

bool search_word(struct node* root, char* word, int current_index) {
    if (current_index == strlen(word)) {
        return root->is_word;
    }

    struct node* contains = darray_contains(root->children, word[current_index]);

    if (contains) {
        return search_word(contains, word, current_index + 1);
    }
    return false;
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

void printDictionary(char** dictionary, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("Word number %d: %s\n", i, dictionary[i]);
    }
}

bool is_word_valid(char* word)
{
    for(int i = 0; word[i] != NULL; i++)
    {
        if(word[i] > 'a' && word[i] < 'z')
        {

        }else return false;
    }

    return true;
}

void add_word_to_dictionary(struct node* root, FILE* file)
{
    char* word = calloc(20, sizeof(char));

    printf("\nEnter word to insert to dictionary...\n");
    printf("      Word : ");



    do
    {
    scanf("%s", word);
    if(is_word_valid(word) != false) break;
    printf("\n Invalid input for word!\n");
    printf("      Word : ");
    }while(1);


    if(search_word(root, word, 0) == true)
    {
       printf("\nThis word already exists in the dectionary!");
    }else
    {
        printf("Successfully inserted word...");

        insert_word(root, word, 0);

        fprintf(file, "%s\n", word);
    }
    free(word);
}

int main() {

    FILE *dict_file;

    dict_file = fopen("dictionary.txt", "a");

    if (dict_file == NULL)
    {
        printf("Unable to open the file.\n");
        return 0;
    }

    struct node* root = create_node(' ');

    insert_word(root, "alex", 0);
    insert_word(root, "albatroz", 0);

    add_word_to_dictionary(root, dict_file);

    print_trie(root);

    free(root);

    fclose(dict_file);

    return 0;
}
