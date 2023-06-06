#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define STRINGSIZE 32

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
