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

int main()
{
    char menuchoice[][STRINGSIZE] = {"test1\0",
    "test2\0",
    "test3\0",
    "test4\0"};

    int output = menuOptions(4, menuchoice);

    system("cls");
    printf("%d", output);

    return 0;
}
