#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define STRINGSIZE 16

int menuOptionsRecursive(int count, char menuchoice[][STRINGSIZE], int current)
{
    system("cls");
    for(int i = 0; i < count; i++) // output the options
    {
        if(i == current)
        {
            printf(" > ");
        }
        else
        {
            printf("   ");
        }

        printf("%s\n", menuchoice[i]);
    }
    printf("\n\n");

    char input = getch(); // get user input + do action accordingly
    if(input == 'w')
    {
        if(--current < 0) current = count-1;
    }
    else if(input == 's')
    {
        if(++current >= count) current = 0;
    }
    else if(input == 'e')
    {
        return current;
    }

    return menuOptionsRecursive(count, menuchoice, current);
}

int menuOptions(int count, char menuchoice[][STRINGSIZE]) // menu with multiple options
{
    return menuOptionsRecursive(count, menuchoice, 0);
}


int menuNumbersRecursive(int min, int max, char message[STRINGSIZE], int current)
{
    system("cls");
    printf("%s\n", message); // output
    printf(" > %d\n", current);
    printf("\n\n");

    char input = getch(); // get user input + do action accordingly
    if(input == 'd')
    {
        if(current+1 <= max) current++;
    }
    else if(input == 'a')
    {
        if(current-1 >= min) current--;
    }
    else if(input == 'e') return current;

    return menuNumbersRecursive(min, max, message, current);
}

int menuNumbers(int min, int max, char message[STRINGSIZE]) // menu with increasing/decreasing value
{
    return menuNumbersRecursive(min, max, message, min);
}

void pressanykey() // shortcut function for every time "Press any key to continue" appears
{
    printf("Press any key to continue...\n");
    getch();
    system("cls");
}

void titlescreen() // title screen info
{
    printf("\n");
    printf("  ____                          _       _       _        \n");
    printf(" / ___|    ___   _ __    __ _  | |__   | |__   | |   ___ \n");
    printf(" \\___ \\   / __| | '__|  / _` | | '_ \\  | '_ \\  | |  / _ \\\n");
    printf("  ___) | | (__  | |    | (_| | | |_) | | |_) | | | |  __/\n");
    printf(" |____/   \\___| |_|     \\__,_| |_.__/  |_.__/  |_|  \\___|\n\n\n");

    printf("A game developed by:\n");
    printf(" - Alexandar Hristov (No.2)\n");
    printf(" - Alexandar Todorov (No.3)\n");
    printf(" - Petar Petrov (No.19)\n");
    printf(" - Stiliyan Mandaliev (No.23) from 10A class\n\n");

    printf("Info:\n");
    printf("In this version of scrabble you are given a number of letters each round.\n");
    printf("The goal is to create as many words with them as possible. For each letter you\n");
    printf("used in a word, you gain 1 point. The goal is to get as many points as possible!\n\n\n");

    printf("To navigate the menus:\n");
    printf(" - Use W and S to select an option (if presented with such) and E to confirm.\n");
    printf(" - Use A and D to increase or decrease a value and E to confirm.\n\n\n");

    pressanykey();
}
