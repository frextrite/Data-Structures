#include <stdio.h>
#include <stdlib.h>

struct polynomial {
    int coefficient;
    int exponent;
    struct polynomial *next;
};

struct polynomial *getNewNode() {
    struct polynomial *poly = (struct polynomial*)malloc(sizeof(struct polynomial));
    poly->coefficient = 0;
    poly->exponent = 0;
    poly->next = NULL;
}

void insert(struct polynomial **head, int c, int n) {
    struct polynomial *node = getNewNode();
    node->coefficient = c;
    node->exponent = n;
    if(*head == NULL) {
        *head = node;
    } else {
        struct polynomial *temp = *head;
        while(temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = node;
    }
}

void print(struct polynomial *head) {
    struct polynomial *poly = head;
    while(poly != NULL) {
        printf("%dx^%d ", poly->coefficient, poly->exponent);
        poly = poly->next;
    } 
}

int main() {
    struct polynomial *poly = NULL;
    insert(&poly, 45, 3);
    insert(&poly, 31, 2);
    insert(&poly, 2, 0);
    print(poly);
    return 0;
}