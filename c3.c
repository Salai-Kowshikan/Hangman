#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include "./stack.h"
#include "./linkedlist.h"
#define NAME_MAX 50
#define WORD_MAX 10

struct node *scoreList;
struct treenode
{
    int element;
    char *name;
    struct treenode *left;
    struct treenode *right;
};
struct treenode *T;

void clearScreen();
void printHangman(int incorrectGuessCount);
void playHangman(FILE *file, int n, int *score, char *name, bool *start);
void gameState(int *state);
bool checkArray(char *array, int size, char target);
struct treenode *insert(struct treenode *T, int x, char name[NAME_MAX]);
void writeScoresToFile(struct node *start, const char *filename);
void scores(struct node *start);
void highscores(struct treenode *T);
void deleteTree(struct treenode *root);
void readScoresFromFile(const char *filename, struct node **start);

int BSTcount = 0;
int main()
{
    FILE *file;
    char *filename;
    int n, state, valid;
    char *name = (char *)malloc(NAME_MAX);
    bool restart = true;
    readScoresFromFile("scores.txt", &scoreList);

    srand((unsigned int)time(NULL));

    printf("Ready to play? (0/1): ");
    gameState(&state);

    int score = 0;
    clearScreen();

    while (state == 1)
    {
        if (restart)
        {
            printf("\nPlease enter your name: ");
            fgets(name, NAME_MAX, stdin);
            name[strcspn(name, "\n")] = '\0';
        }

        clearScreen();

        printf(" ** HANGMAN ** \n");
        printf("\n1) Start game\n2) Leaderboard\n");
        bool go = true;
        while (go)
        {
            printf("\nEnter your choice: ");
            int choice;
            scanf("%d", &choice);
            switch (choice)
            {
            case 1:
                go = false;
                break;
            case 2:
                printf("\n");
                // display(scoreList);
                deleteTree(T);
                T = NULL;
                scores(scoreList);
                BSTcount = 0;
                highscores(T);
                break;
            default:
                continue;
            }
        }
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

        playHangman(file, n, &score, name, &restart);
        fclose(file);
        printf("\nAnother game? (0/1): ");
        state = 0;
        gameState(&state);
    }

    return 0;
}

void playHangman(FILE *file, int n, int *score, char *name, bool *restart)
{
    char buffer[WORD_MAX];
    bool keep_reading = true;
    int current_line = 1;
    struct Stack history;
    initializeStack(&history);

    do
    {
        fgets(buffer, WORD_MAX, file);
        int read_line = rand() % 50 + 1;

        if (feof(file))
        {
            fseek(file, 0, SEEK_SET);
            current_line = 1;
            continue;
        }

        if (read_line == current_line)
        {
            keep_reading = false;
            int i, j, c, count = 0, ans = 0, flag = 0;
            //i and j are loop variables, c is the length of the word
            //count is the total number of guesses
            //ans is the number of correct guesses
            //a is the actual array
            //b is the buffer array
            char a[WORD_MAX];
            int x = 0;
            while (buffer[x] != '\0')
            {
                a[x] = buffer[x];
                x++;
            }

            printf("\n");

            char b[WORD_MAX], alpha;
            char dash = '_';

            c = strlen(buffer) - 1;

            for (j = 0; j < c; j++)
            {
                printf("%c ", dash);
                b[j] = dash;
            }

            while (count < WORD_MAX)
            {
                flag = 0;
                printf("\n\n\nPlease Enter a Character:");
                alpha = getch();
                push(&history, alpha);
                clearScreen();
                if (!isalpha(alpha))
                {
                    printf("Invalid input! Please enter an alphabet letter.\n");
                    printf("\n");
                    printStack(&history);
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
                    if (alpha == a[i])
                    {
                        b[i] = a[i];
                        flag = 1;
                        ans++;
                    }
                }
                printf("\n");
                printStack(&history);
                for (i = 0; i < c; i++)
                {
                    printf("%c ", b[i]);
                }

                printf("\n");
                if (flag == 0)
                {
                    count++;
                    printf("\n%c is a Wrong Guess", alpha);
                    printf("\n(You Have %d More Guesses Left)", WORD_MAX - count);
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
                *restart = false;
            }
            else
            {

                printf("\n\n\nNo more chances left :(\nThe word is %s", buffer);
                printf("\n  You Lost !!\n **SORRY YOU ARE HANGED**");
                scoreList = create(scoreList, *score, name);
                printf("\n");
                printf("\nName: %s", name);
                printf("\nYour current score: %d", *score);
                // display(scoreList);
                *score = 0;
                *restart = true;
                break;
            }
            printf("\nName: %s", name);
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
    case 2:
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
    case 4:
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
    case 6:
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
    case 8:
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

void gameState(int *state)
{
    bool valid = false;
    while (!valid)
    {
        scanf("%d", state);
        getchar();
        if (*state == 0)
        {
            printf("\nByeeeee!\n");
            writeScoresToFile(scoreList, "scores.txt");
            valid = true;
        }
        else if (*state == 1)
        {
            valid = true;
        }
        else
        {
            printf("\nPlease enter a valid option!\n");
        }
    }
}
struct treenode *insert(struct treenode *T, int x, char name[NAME_MAX])
{
    if (T == NULL)
    {
        T = (struct treenode *)malloc(sizeof(struct treenode));
        if (T == NULL)
        {
            printf("Memory allocation failed\n");
        }
        else
        {
            T->element = x;
            T->name = (char *)malloc(strlen(name) + 1);
            if (T->name == NULL)
            {
                printf("Memory allocation failed\n");
                free(T);
                return NULL;
            }
            strcpy(T->name, name);
            T->right = T->left = NULL;
        }
        return T;
    }
    else if (x > T->element)
    {
        T->right = insert(T->right, x, name);
    }
    else if (x <= T->element)
    {
        T->left = insert(T->left, x, name);
    }
    return T;
}

void scores(struct node *start)
{
    struct node *ptr;
    ptr = start;
    while (ptr != NULL)
    {
        T = insert(T, ptr->data, ptr->name);
        ptr = ptr->next;
    }
}
void highscores(struct treenode *T)
{
    if (T != NULL && BSTcount < 5)
    {
        highscores(T->right);

        if (BSTcount < 5)
        {
            BSTcount++;
            printf("%d) %s - %d\n", BSTcount, T->name, T->element);
        }

        highscores(T->left);
    }
}
void deleteTree(struct treenode *root)
{
    if (root == NULL)
    {
        return;
    }
    deleteTree(root->left);
    deleteTree(root->right);
    free(root->name);
    free(root);
}
void writeScoresToFile(struct node *start, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error opening file for writing\n");
        return;
    }

    struct node *current = start;
    while (current != NULL)
    {
        fprintf(file, "%s,%d\n", current->name, current->data);
        current = current->next;
    }

    fclose(file);
    // printf("Scores written to %s\n", filename);
}
void readScoresFromFile(const char *filename, struct node **start)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file for reading\n");
        return;
    }

    char line[100];
    while (fgets(line, sizeof(line), file) != NULL)
    {
        char *token = strtok(line, ",");
        if (token != NULL)
        {
            char name[NAME_MAX];
            strcpy(name, token);

            token = strtok(NULL, ",");
            if (token != NULL)
            {
                int score = atoi(token);
                *start = create(*start, score, name);
            }
        }
    }

    fclose(file);
    // printf("Scores read from %s\n", filename);
}
