#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct node {
    char value;
    struct darray* children;
    bool is_word;
};

struct darray {
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

struct node* create_node(char value) {
    struct node* new_node = calloc(1, sizeof(struct node));

    new_node->value = value;
    new_node->children = create_darray(4);
    new_node->is_word = false;

    return new_node;
}

struct node* darray_contains(struct darray* arr, char letter) {
    for(int i = 0; i < arr->count; i++) {
        if(arr->nodes[i]->value == letter) {
            return arr->nodes[i];
        }
    }

    return NULL;
}

void darray_add(struct darray* arr, char letter) {
    arr->nodes[arr->count++] = create_node(letter);
}


void insert_word(struct node* root, char* word, int current_index) {
    struct node* contains = darray_contains(root->children, word[current_index]);

    if(contains) {
        insert_word(contains, word, current_index + 1);
    } else {
        struct node* iterator = root;

        for(int i = current_index; i < strlen(word); i++) {
            darray_add(iterator->children, word[i]);

            iterator = iterator->children->nodes[iterator->children->count - 1];
        }

        iterator->is_word = true;

        return;
    }

    if(current_index == strlen(word) - 1) {
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

void free_darray(struct darray* arr) {
    free(arr->nodes);
    free(arr);
}

void free_trie(struct node* root) {
    if(root->children->count == 0) {
        free_darray(root->children);
        free(root);

        return;
    }

    for(int i = 0; i < root->children->count; i++) {
        free_trie(root->children->nodes[i]);
    }

    free_darray(root->children);
    free(root);
}

struct node* generate_trie(FILE* dictionary) {
    struct node* root = create_node(' ');

    char* word = calloc(20, sizeof(char));

    while(true) {
        if(fscanf(dictionary, "%s", word) == EOF) {
            break;
        } else {
            insert_word(root, word, 0);
        }
    }

    free(word);

    return root;
}

int main() {

    FILE* dictionary = fopen("dictionary.txt", "r");

    struct node* root = generate_trie(dictionary);

    print_trie(root);

    free_trie(root);

    fclose(dictionary);

    return 0;
}
