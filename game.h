#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

int playRound(int count) // singular round; same for versus and solo
{
    char letters[64];
    char input[64] = "abc";
    int points = 0;
    printf("Letters: ");
    for(int i = 0; i < count; i++) // generate and print letters
    {
        letters[i] = 'a' + rand()%26;
        printf("%c ", letters[i]);
    }
    letters[count] = '\0';
    printf("\n\nEnter words with the given letters. When you finish, input a minus (-):\n");

    while(1) // get words from player
    {
        scanf("%s", input);
        input[strlen(input)] = '\0';
        if(strcmp(input, "-\0") == 0) break;

        for(int i = 0; i < strlen(input); i++) // to do: is word repeated? is word in trie?
        {
            if(input[i] < 'a' || input[i] > 'z') // invalid letter: not a-z
            {
                printf("Invalid word provided! Words must be written with a-z only\n");
                points -= i;
                break;
            }
            int j = 0;
            for(j = 0; j < count; j++) // is each letter in letters[]?
            {
                if(input[i] == letters[j])
                {
                    points++;
                    letters[j] -= ('a' - 'A');
                    break;
                } // used letters are turned into capital letters so they can no longer be used
            }
            if(j == count) // letter not in letters[]
            {
                printf("Invalid word provided! Used ungiven letter.\n");
                points -= i;
                break;
            }
        }

        for(int i = 0; i < count; i++) // revert used letters from capital
        {
            if(letters[i] >= 'A' && letters[i] <= 'Z')
            {
                letters[i] += ('a' - 'A');
            }
        }
    }

    return points;
}

int solo(int rounds, int letters)
{
    system("cls");
    int points = 0;
    for(int i = 0; i < rounds; i++) // each round
    {
        printf("Round %d/%d:\n\n", i+1, rounds);
        points += playRound(letters);
        system("cls");
    }
    printf("Game finished! Player got %d point/s!\n\nPress any key to continue...", points);
    getch();
    return points;
}

int versus(int rounds, int letters)
{
    system("cls");
    return 11;
}
