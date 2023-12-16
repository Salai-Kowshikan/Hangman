#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>

void clearScreen();
void printHangman(int incorrectGuessCount);

int main()
{
    FILE *file;
    char *filename;
    char buffer[10];
    int n, a;

    srand((unsigned int)time(NULL));

    printf("Ready to play?(0/1)");
    scanf("%d", &a);
    while (a == 1)
    {
        printf(" ** HANGMAN ** \n");
        printf("Levels:\n1.Easy\n2.Medium\n3.Hard\n");
        printf("enter level:");
        scanf("%d", &n);
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
            printf("enter again:(\n");
            break;
        }

        int read_line = rand() % 50 + 1;
        file = fopen(filename, "r");
        if (file == NULL)
        {
            printf("error opening file\n");
            return 1;
        }
        // printf("file opened\n");
        bool keep_reading = true;
        int current_line = 1;
        clearScreen();
        do
        {
            fgets(buffer, 10, file);
            if (read_line == current_line)
            {
                keep_reading = false;
                int i, j, c, count = 0, ans = 0, flag = 0;
                char a[1][10]; // Characters to Guess
                int x = 0;
                while (buffer[x] != '\0')
                {
                    a[0][x] = buffer[x];
                    x++;
                }
                /* Test code to check if the word has been taken properly
                for(int i=0;i<x;i++){
                    printf("%c",a[0][i]);
                }
                */
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
                    printf("\n\n\nPlz Enter a Character:");
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
                }
                else
                {

                    printf("\n\n\nNo more chances left :(\nThe word is %s", buffer);
                    printf("\n  You Lost !!\n **SORRY YOU ARE HANGED**");
                }
            }
            current_line++;
        } while (keep_reading);
        fclose(file);

        printf("\n ** HANGMAN ** \n");
        printf("Levels:\n1.Easy\n2.Medium\n3.Hard\n");
        printf("\nAnother game?(0/1)");
        scanf("%d", &a);
    }
    return 0;
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