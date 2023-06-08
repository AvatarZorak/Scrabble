#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "betterPointCalc.h"

#define ARRSIZE 64

/*int playRound(int count, int seed) // singular round; same for versus and solo
{
    srand(seed);
    char letters[ARRSIZE];
    char input[ARRSIZE] = "abc";
    char usedwords[ARRSIZE][ARRSIZE];
    for(int i = 0; i < ARRSIZE; i++) strcpy(usedwords[i], "");
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

        for(int i = 0; i < STRINGSIZE && strcmp(usedwords[i], "\0") != 0; i++) // check if word is used already
        {
            if(strcmp(input, usedwords[i]) == 0)
            {
                printf("Invalid word provided! Words cannot be repeated\n");
                strcpy(input, "");
            }
        }
        if(strcmp(input, "\0") == 0) continue;

        for(int i = 0; i < strlen(input); i++) // to do: is word in trie?
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

            for(int i = 0; 1; i++) // add word to used words
            {
                if(strcmp(usedwords[i], "\0") == 0)
                {
                    strcpy(usedwords[i], input);
                    break;
                }
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
}*/

int solo(int rounds, int letters)
{
    system("cls");
    int points = 0;
    for(int i = 0; i < rounds; i++) // each round
    {
        int seed = time(NULL);
        printf("Round %d/%d:\n\n", i+1, rounds);
        points += playRound(letters, seed);
        system("cls");
    }
    printf("Game finished! Player got %d point/s!\n\nPress any key to continue...", points);
    getch();
    return points;
}

int versus(int rounds, int letters)
{
    system("cls");
    int points1 = 0;
    int points2 = 0;
    for(int i = 0; i < rounds; i++) // each round
    {
        int seed = time(NULL);
        printf("Round %d/%d of Player#1:\n\n", i+1, rounds);
        points1 += playRound(letters, seed);
        system("cls");

        printf("Player#1 finished their round! Time for Player#2!\n\nPress any key to continue...");
        getch();
        system("cls");

        printf("Round %d/%d of Player#2:\n\n", i+1, rounds);
        points2 += playRound(letters, seed);
        system("cls");

        if(i+1 != rounds)
        {
            printf("Player#2 finished their round! Time for Player#1!\n\nPress any key to continue...");
            getch();
            system("cls");
        }
    }
    printf("Game finished! Player#1 got %d point/s and Player#2 got %d point/s!\n\nPress any key to continue...", points1, points2);
    getch();
    if(points1 > points2) return points1;
    else return points2;
}
