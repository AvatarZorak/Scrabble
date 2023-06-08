#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#define ARRSIZE 64
#define STRINGSIZE 32


int calculatePoints(const char* word, const char* letters) {
    int points = 0;
    int lettersCount[26] = {0};


    for (int i = 0; letters[i] != '\0'; i++) {
        if (letters[i] >= 'a' && letters[i] <= 'z') {
            lettersCount[letters[i] - 'a']++;
        }
    }

    for (int i = 0; word[i] != '\0'; i++) {
        char letter = word[i];
        if (letter >= 'a' && letter <= 'z' && lettersCount[letter - 'a'] > 0) {
            points++;
            lettersCount[letter - 'a']--;
        }
    }

    return points;
}

int playRound(int count, int seed) {
    srand(seed);
    char letters[ARRSIZE];
    char input[ARRSIZE] = "abc";
    char usedwords[ARRSIZE][ARRSIZE];
    for (int i = 0; i < ARRSIZE; i++) strcpy(usedwords[i], "");

    printf("Letters: ");
    for (int i = 0; i < count; i++) {
        letters[i] = 'a' + rand() % 26;
        printf("%c ", letters[i]);
    }
    letters[count] = '\0';
    printf("\n\nEnter words with the given letters. When you finish, input a minus (-):\n");

    int points = 0;

    while (1) {
        scanf("%s", input);
        input[strlen(input)] = '\0';
        if (strcmp(input, "-\0") == 0) break;

        // Check if word is already used
        for (int i = 0; i < ARRSIZE && strcmp(usedwords[i], "\0") != 0; i++) {
            if (strcmp(input, usedwords[i]) == 0) {
                printf("Invalid word provided! Words cannot be repeated\n");
                strcpy(input, "");
            }
        }
        if (strcmp(input, "\0") == 0) continue;

        int wordPoints = calculatePoints(input, letters);
        points += wordPoints;

        if (wordPoints < strlen(input)) {
            printf("Invalid word provided! Words must be written with a-z only\n");
        } else if (wordPoints == 0) {
            printf("Invalid word provided! Used ungiven letter.\n");
        } else {
            for (int i = 0; i < ARRSIZE; i++) {
                if (strcmp(usedwords[i], "\0") == 0) {
                    strcpy(usedwords[i], input);
                    break;
                }
            }
        }
    }

    return points;
}
