#include <stdio.h>
#include "mainmenu.h"

int main()
{
    int rounds = 10; // rounds count
    int letters = 10; // letters count

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
            printf("Count of rounds: %d\n", rounds);
            printf("Count of letters given per round: %d\n\n", letters);
            pressanykey();
        }
        else if(output == 2) // MUST MAKE TO ADD WORD IN DICTIONARY
        {
            system("cls");
            pressanykey();
        }
        else if(output == 1) // settings
        {
            output = settings();
            if(output > 0) rounds = output;
            else letters = (output * -1);
        }
    }

    return 0;
}
