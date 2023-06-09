#include <stdio.h>
#include "menu.h"
#include "game.h"

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

int mainmenu()
{
    char menu[][STRINGSIZE] = {
        "Start game\0",
        "Settings\0",
        "Add word to dictionary\0",
        "Stats\0",
        "Exit\0"
    };

    return menuOptions(5, menu);
}

void exitgame()
{
    system("cls");
    printf("You are exiting the game!\n");
}

int editLetters()
{
    return menuNumbers(1, 20, "Select new number of letters:");
}

int editRounds()
{
    return menuNumbers(1, 20, "Select new number of rounds:");
}

int settings()
{
    char menu[][STRINGSIZE] = {
        "Edit number of rounds\0",
        "Edit number of letters\0",
        "Back\0"
    };

    int output = menuOptions(3, menu);
    if(output == 1) return (editLetters() * -1); // letters
    else if(output == 2) return 0; // back
    else return editRounds(); // rounds
}

int gamemenu(int rounds, int letters)
{
    char menu[][STRINGSIZE] = {
        "Solo\0",
        "Versus\0",
        "Back\0"
    };

    int output = menuOptions(3, menu);
    if(output == 1) return versus(rounds, letters); // versus
    else if(output == 2) return -1; // back
    else return solo(rounds, letters); // solo
}
