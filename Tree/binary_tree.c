#include <stdio.h>

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

struct Tree* insertLeft(struct Tree *tree, int data) {
    if(tree->left == NULL) {
        tree->left = createTree(data);
    }
    return tree->left;
}

struct Tree* insertRight(struct Tree *tree, int data) {
    if(tree->right == NULL) {
        tree->right = createTree(data);
    }
    return tree->right;
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

int main() {
    struct Tree *root = createTree(5);
    struct Tree *rl = insertLeft(root, 3);
    struct Tree *rr = insertRight(root, 7);
    struct Tree *rll = insertLeft(rl, 2);
    struct Tree *rlr = insertRight(rl, 4);
    struct Tree *rrl = insertLeft(rr, 6);
    printInorder(root);
    printf("\n");
    printPreorder(root);
    printf("\n");
    printPostorder(root);
    printf("\n");
    return 0;
}