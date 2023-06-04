#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define STRINGSIZE 16

int menuOptionsRecursive(int count, char menuchoice[][STRINGSIZE], int current)
{
    system("cls");
    for(int i = 0; i < count; i++)
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

    char input = getch();
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

int menuOptions(int count, char menuchoice[][STRINGSIZE])
{
    return menuOptionsRecursive(count, menuchoice, 0);
}


int menuNumbersRecursive(int min, int max, char message[STRINGSIZE], int current)
{
    system("cls");
    printf("%s\n", message);
    printf(" > %d\n", current);
    printf("\n\n");

    char input = getch();
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

int menuNumbers(int min, int max, char message[STRINGSIZE])
{
    return menuNumbersRecursive(min, max, message, min);
}
