#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

struct node *create(struct node *start, int num, char name[50])
{
    struct node *ptr, *new_node;
    new_node = (struct node *)malloc(sizeof(struct node));
    new_node->data = num;
    new_node->name = malloc(50);
    strcpy(new_node->name, name); 

    if (start == NULL)
    {
        new_node->next = NULL;
        start = new_node;
    }
    else
    {
        ptr = start;
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        ptr->next = new_node;
        new_node->next = NULL;
    }
    return start;
}


void display(struct node *start)
{
    struct node *ptr;
    ptr = start;
    while (ptr != NULL)
    {
        printf("%s : %d - ",ptr->name, ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
}
void freeList(struct node *start)
{
    struct node *ptr, *temp;
    ptr = start;
    while (ptr != NULL)
    {
        temp = ptr;
        ptr = ptr->next;
        free(temp->name);
        free(temp);
    }
}
