#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>

const char* dictionary_file_name = "dictionary.txt";
const char* binary_file_name = "trie.bin";

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

void free_trie(struct node* root) {
    if (root == NULL) {
        return;
    }
    for (int i = 0; i < root->children->count; i++) {
        free_trie(root->children->nodes[i]);
    }
    free(root->children->nodes);
    free(root->children);
    free(root);
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

bool is_word_valid(char* word)
{
    for(int i = 0; word[i] != '\0'; i++)
    {
        if(word[i] < 'a' || word[i] > 'z')
        {
            return false;
        }
    }

    return true;
}


void add_word_to_dictionary(struct node* root, const char* filename)
{
    FILE* dictionary = fopen(filename, "a");

    char* word;

    printf("\nEnter word to insert to dictionary...\n");

    do
    {
        printf("\nInsert word : ");
        word = calloc(20, sizeof(char));

        scanf("%s", word);

        if(is_word_valid(word) != false) break;

        printf("\nInvalid input for word!\n");
        free(word);

    }while(1);


    if(search_word(root, word, 0) == true)
    {
       printf("\nThis word already exists in the dictionary!");
    }else
    {
        printf("\nSuccessfully inserted word!\n");

        insert_word(root, word, 0);

        fprintf(dictionary, "%s\n", word);
    }

    free(word);

    fclose(dictionary);
}


void serialize_trie(struct node* root, FILE* file) //separate the trie
{
    if (root == NULL)
    {
        return;
    }

    fwrite(&(root->value), sizeof(char), 1, file);
    fwrite(&(root->is_word), sizeof(bool), 1, file);
    int children_count = root->children->count;
    fwrite(&children_count, sizeof(int), 1, file); //puska count, za da pishem dumata dokato ne svurshi

    for (int i = 0; i < children_count; i++)
    {
        serialize_trie(root->children->nodes[i], file);
    }

}

void write_trie_to_file(struct node* root, const char* filename)
{
    FILE* file = fopen(filename, "wb");

    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    serialize_trie(root, file);

    fclose(file);
}

struct node* deserialize_trie(FILE* file)
{
    struct node* root = create_node('\0');

    fread(&(root->value), sizeof(char), 1, file);
    fread(&(root->is_word), sizeof(bool), 1, file);

    int children_count;
    fread(&children_count, sizeof(int), 1, file);

    root->children = create_darray(4);

    for (int i = 0; i < children_count; i++)
    {
        struct node* child = deserialize_trie(file);
        darray_add(root->children, child->value);
        root->children->nodes[root->children->count - 1] = child;
    }

    return root;
}

struct node* read_trie_from_file(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error opening file for reading!\n");
        return NULL;
    }

    struct node* root = deserialize_trie(file);

    fclose(file);

    return root;
}

char* read_word(FILE* file) {
    int length;
    fread(&length, sizeof(int), 1, file);

    char* word = malloc((length + 1) * sizeof(char));
    fread(word, sizeof(char), length, file);
    word[length] = '\0';

    return word;
}

void delete_trie_data(const char* filename)
{
    FILE* file = fopen(filename, "r+");
    if (file == NULL)
    {
        printf("Error opening file for truncation!\n");
        return;
    }

    // Truncate the file to size 0
    if (ftruncate(fileno(file), 0) == 0)
    {
        printf("Data in the binary file deleted successfully.\n");
    } else {
        printf("Error deleting data in the binary file.\n");
    }

    fclose(file);
}

struct node* generate_trie(const char* filename) {

    FILE* dictionary = fopen(filename, "r");

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

    fclose(dictionary);

    return root;
}
// |\---/|
// | o_o |
//  \_^_/

int main()
{

    FILE *dict_file;

    dict_file = fopen("dictionary.txt", "a");

    if (dict_file == NULL)
    {
        printf("Unable to open the file.\n");
        return 0;
    }

    // Read the Trie from the file
    struct node* root;
    FILE* bin_file = fopen(binary_file_name, "r");
    if(fgetc(bin_file) != EOF){
        fclose(bin_file);
        root = read_trie_from_file(binary_file_name);
        delete_trie_data(binary_file_name); //deleting it, because we read the tree, saved it in the root
    } else{
        root = generate_trie(dictionary_file_name);
        fclose(bin_file);
    }

    print_trie(root);
    // Perform operations on the Trie
    add_word_to_dictionary(root, dictionary_file_name);

    print_trie(root);

    write_trie_to_file(root, binary_file_name);
    
    // Free the Trie
    free_trie(root);

    fclose(dict_file);

}
