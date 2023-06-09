#include <stdio.h>
#include "mainmenu.h"

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
    } else{
        root = generate_trie(dictionary_file_name);
        fclose(bin_file);
    }

    int rounds = 10; // rounds count
    int letters = 10; // letters count
    int highscore = 0;

    titlescreen();
    while(1)
    {
        int output = mainmenu();

        if(output == 4) // exit
        {
            exitgame();
            break;
        }
        else if(output == 3) // stats
        {
            system("cls");
            printf("Displaying stats of current playing session:\n\n");
            printf("Highscore: %d\n", highscore);
            printf("Count of rounds: %d\n", rounds);
            printf("Count of letters given per round: %d\n\n", letters);
            pressanykey();
        }
        else if(output == 2) // add dictionary
        {
            delete_trie_data(binary_file_name);
            add_word_to_dictionary(root, dictionary_file_name);
            write_trie_to_file(root, binary_file_name);
        }
        else if(output == 0) // game
        {
            int score = gamemenu(rounds, letters);
            if(score > highscore) highscore = score;
        }
        else if(output == 1) // settings
        {
            output = settings();
            if(output > 0) rounds = output;
            else if(output < 0) letters = (output * -1);
        }
    }

    free_trie(root);

    fclose(dict_file);

    return 0;
}

// |\---/|
// | o_o |
//  \_^_/
