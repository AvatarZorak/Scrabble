#include <stdio.h>
#include <time.h>
#include "mainmenu.h"

int main()
{
    srand(time(NULL));
    int rounds = 10; // rounds count
    int letters = 10; // letters count
    int highscore = 0;

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
            printf("Highscore: %d\n", highscore);
            printf("Count of rounds: %d\n", rounds);
            printf("Count of letters given per round: %d\n\n", letters);
            pressanykey();
        }
        else if(output == 2) // MUST MAKE TO ADD WORD IN DICTIONARY
        {
            system("cls");
            pressanykey();
        }
        else if(output == 0) // game
        {
            int score = gamemenu(rounds, letters);
            if(score > highscore) highscore = score;
        }
        else if(output == 1) // settings
        {
            output = settings();
            if(output > 0) rounds = output;
            else if(output < 0) letters = (output * -1);
        }
    }

    return 0;
}
