#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int value;
    struct Node *next;
};

void push(struct Node **stack, int x) {
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->value = x;
    node->next = *stack;
    *stack = node;
}

int pop(struct Node **stack) {
    if(*stack == NULL) return -1;

    struct Node *current = *stack;
    int x = current->value;
    *stack = current->next;
    free(current);
    return x;
}

int main() {
    struct Node *stack = NULL;
    push(&stack, 5);
    push(&stack, 43);
    push(&stack, 21);
    push(&stack, 9);
    printf("Popped element: %d\n", pop(&stack));
    printf("Popped element: %d\n", pop(&stack));
    printf("Popped element: %d\n", pop(&stack));
    push(&stack, 4);
    printf("Popped element: %d\n", pop(&stack));
    printf("Popped element: %d\n", pop(&stack));

    return 0;
}