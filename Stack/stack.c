#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Stack {
    int top;
    int max_size;
    int* array;
};

struct Stack *createStack(int max_size) {
    struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
    stack->top = -1;
    stack->max_size = max_size;
    stack->array = (int *)malloc(sizeof(int) * max_size);
}

bool push(struct Stack *stack, int x) {
    if(stack->top == stack->max_size-1) {
        printf("Stack is full.\n");
        return false;
    }
    *((stack->array) + stack->top + 1) = x;
    stack->top = stack->top + 1;
    return true;
}

int pop(struct Stack *stack) {
    if(stack->top == -1) {
        printf("Stack is empty.\n");
        return -1;
    }
    int x = *((stack->array) + stack->top);
    stack->top = stack->top - 1;
    return x;
}

int main() {
    struct Stack *stack = createStack(100);
    push(stack, 5);
    push(stack, 43);
    push(stack, 21);
    push(stack, 9);
    printf("Popped element: %d\n", pop(stack));
    printf("Popped element: %d\n", pop(stack));
    printf("Popped element: %d\n", pop(stack));
    printf("Popped element: %d\n", pop(stack));
    printf("Popped element: %d\n", pop(stack));
    return 0;
}