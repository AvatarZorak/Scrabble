#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "betterPointCalc.h"

#define ARRSIZE 64

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
