#include <stdio.h>
#include "menu.h"

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
