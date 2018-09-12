#include <stdio.h>
#include <stdlib.h>

// struct Node *start = NULL;

struct Node {
    int value;
    struct Node *next;
};

struct Node *get_new_node() {
    return (struct Node *)malloc(sizeof(struct Node));
}

void insert(struct Node **start, int x) {
    struct Node *temp = *start;
    struct Node *new_node = get_new_node();

    if(temp == NULL) {
        new_node->value = x;
        new_node->next = NULL;
        *start = new_node;
    } else {
        if(temp->value > x) {
            new_node->value = x;
            new_node->next = temp;
            *start = new_node;
        } else {
            while(temp->next != NULL && temp->value < x) {
                temp = temp->next;
            }
            new_node->value = x;
            new_node->next = temp->next;
            temp->next = new_node;
        }
    }
}

void print(struct Node *start) {
    struct Node *temp = start;
    printf("\nLinked List\n");
    while(temp != NULL) {
        printf("%d ", temp->value);
        temp = temp->next;
    }
}

int main() {
    struct Node *start = NULL;
    insert(&start, 10);
    insert(&start, 15);
    insert(&start, 16);
    print(start);
    insert(&start, 20);
    insert(&start, 5);
    print(start);
    return 0;
}