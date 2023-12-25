// stack.c

#include "stack.h"
#include <stdio.h>

void initializeStack(struct Stack *stack) {
    stack->top = -1; // Initialize top to -1 to indicate an empty stack
}

void push(struct Stack *stack, char value) {
    if (isFull(stack)) {
        printf("Stack overflow! Cannot push more elements.\n");
        return;
    }

    stack->arr[++stack->top] = value;
}

char pop(struct Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow! Cannot pop from an empty stack.\n");
        return '\0'; // Return a sentinel value indicating an error
    }

    return stack->arr[stack->top--];
}

int isEmpty(struct Stack *stack) {
    return stack->top == -1;
}

int isFull(struct Stack *stack) {
    return stack->top == MAX_SIZE - 1;
}

void printStack(struct Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty.\n");
        return;
    }

    printf("History: ");
    for (int i = 0; i <= stack->top; ++i) {
        printf("%c ", stack->arr[i]);
    }
    printf("\n");
}
