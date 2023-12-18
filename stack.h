// stack.h

#ifndef STACK_H
#define STACK_H

#define MAX_SIZE 100  // Adjust the maximum size as needed

struct Stack {
    int top;
    char arr[MAX_SIZE];
};

void initializeStack(struct Stack *stack);
void push(struct Stack *stack, char value);
char pop(struct Stack *stack);
int isEmpty(struct Stack *stack);
int isFull(struct Stack *stack);
void printStack(struct Stack *stack); // New function to print the stack

#endif
