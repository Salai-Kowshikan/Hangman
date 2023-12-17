#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>

void clearScreen();
void printHangman(int incorrectGuessCount);
void playHangman(FILE *file, int n, int *score);
void gameState(int *a);
bool checkArray(char *array, int size, char target);

int main()
{
    FILE *file;
    char *filename;
    int n, a, valid;

    srand((unsigned int)time(NULL));

    printf("Ready to play? (0/1): ");
    gameState(&a);

    int score = 0;
    clearScreen();

    while (a == 1)
    {
        printf(" ** HANGMAN ** \n");
        printf("Levels:\n1.Easy\n2.Medium\n3.Hard\n");
        printf("Enter level:");
        scanf("%d", &n);
        clearScreen();

        switch (n)
        {
        case 1:
            filename = "easy.txt";
            break;
        case 2:
            filename = "mid.txt";
            break;
        case 3:
            filename = "hard.txt";
            break;
        default:
            printf("Invalid level. Enter again.\n");
            continue;
        }

        file = fopen(filename, "r");
        if (file == NULL)
        {
            printf("Error opening file\n");
            return 1;
        }

        playHangman(file, n, &score);
        fclose(file);

        printf("\n ** HANGMAN ** \n");
        printf("Levels:\n1.Easy\n2.Medium\n3.Hard\n");
        printf("\nAnother game? (0/1): ");
        a = 0;
        gameState(&a);
    }

    return 0;
}

void playHangman(FILE *file, int n, int *score)
{
    char buffer[10];
    bool keep_reading = true;
    int current_line = 1;

    do
    {
        fgets(buffer, 10, file);
        int read_line = rand() % 50 + 1;

        if (feof(file))
        {
            // End of file reached, seek back to the beginning
            fseek(file, 0, SEEK_SET);
            current_line = 1;
            continue; // Restart the loop
        }

        if (read_line == current_line)
        {
            keep_reading = false;
            int i, j, c, count = 0, ans = 0, flag = 0;
            char a[1][10];
            int x = 0;
            while (buffer[x] != '\0')
            {
                a[0][x] = buffer[x];
                x++;
            }

            printf("\n");

            char b[10], alpha;
            char d = '_';

            c = strlen(buffer) - 1;

            for (j = 0; j < c; j++)
            {
                printf("%c ", d);
                b[j] = d;
            }

            while (count < 10)
            {
                flag = 0;
                printf("\n\n\nPlease Enter a Character:");
                alpha = getch();
                clearScreen();

                if (!isalpha(alpha))
                {
                    printf("Invalid input! Please enter an alphabet letter.\n");
                    printf("\n");
                    printHangman(count);
                    for (i = 0; i < c; i++)
                    {
                        printf("%c ", b[i]);
                    }

                    printf("\n");
                    continue;
                }

                if (checkArray(b, c, alpha))
                {
                    printf("\nYou have already guessed this character!\n");
                    printf("\n");
                    printHangman(count);
                    for (i = 0; i < c; i++)
                    {
                        printf("%c ", b[i]);
                    }

                    printf("\n");
                    continue;
                }

                for (i = 0; i < c; i++)
                {
                    if (alpha == a[0][i])
                    {
                        b[i] = a[0][i];
                        flag = 1;
                        ans++;
                    }
                }
                printf("\n");
                for (i = 0; i < c; i++)
                {
                    printf("%c ", b[i]);
                }

                printf("\n");
                if (flag == 0)
                {
                    count++;
                    printf("\n%c is a Wrong Guess", alpha);
                    printf("\n(You Have %d More Guesses Left)", 10 - count);
                }
                else
                {
                    printf("\nYou Are Correct !!");
                    printf("\n( You Have %d More letters To Go)", c - ans);
                }
                printHangman(count);
                if (ans == c)
                {
                    break;
                }
            }
            if (ans == c)
            {
                printf("\n You Won !!");
                *score += (1 * n);
            }
            else
            {

                printf("\n\n\nNo more chances left :(\nThe word is %s", buffer);
                printf("\n  You Lost !!\n **SORRY YOU ARE HANGED**");
            }
            printf("\nYour current score: %d", *score);
        }
        current_line++;
    } while (keep_reading);
}

void clearScreen()
{
    system("cls");
}

void printHangman(int incorrectGuessCount)
{
    switch (incorrectGuessCount)
    {
    case 0:
        printf("\n\n\n\n\n");
        break;
    case 1:
        printf("\n\n\n\n\n");
        printf("_____\n");
        printf("|   |\n");
        printf("|   O\n");
        printf("|    \n");
        printf("|    \n");
        break;
    case 3:
        printf("\n\n\n\n\n");
        printf("_____\n");
        printf("|   |\n");
        printf("|   O\n");
        printf("|   |\n");
        printf("|    \n");
        break;
    case 5:
        printf("\n\n\n\n\n");
        printf("_____\n");
        printf("|   |\n");
        printf("|   O\n");
        printf("|  /|\n");
        printf("|    \n");
        break;
    case 7:
        printf("\n\n\n\n\n");
        printf("_____\n");
        printf("|   |\n");
        printf("|   O\n");
        printf("|  /|\\\n");
        printf("|    \n");
        break;
    case 9:
        printf("\n\n\n\n\n");
        printf("_____\n");
        printf("|   |\n");
        printf("|   O\n");
        printf("|  /|\\\n");
        printf("|  / \n");
        break;
    case 10:
        printf("\n\n\n\n\n");
        printf("_____\n");
        printf("|   |\n");
        printf("|   O\n");
        printf("|  /|\\\n");
        printf("|  / \\\n");
        break;
    }
}

bool checkArray(char *array, int size, char target)
{
    for (int i = 0; i < size; i++)
    {
        if (array[i] == target)
        {
            return true;
        }
    }
    return false;
}


void gameState(int *a)
{
    bool valid = false;
    while (!valid)
    {
        scanf("%d", a);
        getchar();
        if (*a==0) {
            printf("\nByeeeee!\n");
            valid = true;
        } else if (*a==1){
            valid=true;
        } else {
            printf("\nPlease enter a valid option!\n");
        }
    }
}
