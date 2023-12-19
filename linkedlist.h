#ifndef LINKEDLIST_H
#define LINKEDLIST_H

struct node
{
    int data;
    char *name;
    struct node *next;
};

struct node *create(struct node *start, int num,char name[50]);
void display(struct node *start);
void freeList(struct node *start);

#endif /* LINKEDLIST_H */
