#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Tree {
    int value;
    struct Tree *left;
    struct Tree *right;
};

struct Tree* createTree(int value) {
    struct Tree *tree = (struct Tree*)malloc(sizeof(struct Tree));
    tree->value = value;
    tree->left = NULL;
    tree->right = NULL;
    return tree;
}

struct Tree* insertNode(struct Tree *tree, int value) {
    if(tree->value > value) {
        if(tree->left == NULL) {
            struct Tree *node = createTree(value);
            tree->left = node;
            return node;
        }
        return insertNode(tree->left, value);
    }
    if(tree->value <= value) {
        if(tree->right == NULL) {
            struct Tree *node = createTree(value);
            tree->right = node;
            return node;
        }
        return insertNode(tree->right, value);
    }
}

void printPreorder(struct Tree *tree) {
    if(tree == NULL)
        return;
    printf("%d ", tree->value);
    printPreorder(tree->left);
    printPreorder(tree->right);
}

void printPostorder(struct Tree *tree) {
    if(tree == NULL)
        return;
    printPostorder(tree->left);
    printPostorder(tree->right);
    printf("%d ", tree->value);
}

void printInorder(struct Tree *tree) {
    if(tree == NULL)
        return;
    printInorder(tree->left);
    printf("%d ", tree->value);
    printInorder(tree->right);
}

struct Tree* search(struct Tree *node, int x) {
    if(node == NULL) {
        return NULL;
    }
    if(node->value == x) {
        return node;
    }
    if(node->value > x) {
        return search(node->left, x);
    }
    if(node->value < x) {
        return search(node->right, x);
    }
}

int main() {
    struct Tree *tree = createTree(50);
    insertNode(tree, 76);
    insertNode(tree, 21);
    insertNode(tree, 4);
    insertNode(tree, 32);
    insertNode(tree, 100);
    insertNode(tree, 64);
    insertNode(tree, 52);
    printInorder(tree);
    printf("\n");
    if(search(tree, 64))
        printf("64 found\n");
    else
        printf("64 doesnt exist\n");

    if(search(tree, 89))
        printf("89 found\n");
    else
        printf("89 doesnt exist\n");
    return 0;
}