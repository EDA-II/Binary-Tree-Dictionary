#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "utils.h"
#include "commons.h"
#include "tree.h"


void init_tree(Tree *t) {
    t->root = NULL;
    t->size = 0;
//    printf("Initialized...\n");
}

void clearPostOrder(Node *node) {
    // Base case: the node is a leaf
    if (node->left == NULL && node->right == NULL) {
       free(node);
    }

    // Recursive Case
    else {
       // Delete the whole left branch
       if (node->left != NULL){
           clearPostOrder(node->left);
       }
       // Delete the whole right branch
       if (node->right != NULL){
           clearPostOrder(node->right);
       }
    }
}

void clear_tree(Tree *t) {
    clearPostOrder(t->root);
    init_tree(t);
}

Node *createNode(char *word) {

    Node *newNode = (Node *) malloc(sizeof(Node));
    strcpy(newNode->data, word);
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}


Node *insertNode(Node *node, char *word) {
    // Base case: position where the new node has to be inserted is found
    if (node == NULL) {
        node = createNode(word);
    } else { // Recursive case:
        if (strcmp(word, node->data) > 0) { // Element we want to insert is greater than the current root of the subtree (word > node->data)
            return insertNode(node->right, word);
        } else if (strcmp(word, node->data) < 0) { // Element we want to insert is lower than the current root of the subtree (word < node->data)
            return insertNode(node->left, word);
        }
    }

    return node;
}

Node *findNode(Node *node, char *word) {
    if (node == NULL){ // Base case 1: the node is not found.
        return NULL;
    } else {
        if (strcmp(word, node->data) == 0) { // Base case 2: We find the node
            return node;
        }
        // Recursive case:
        else if (strcmp(word, node->left->data) > 0) {
            return findNode(node->right, word);
        } else {
            return findNode(node->left, word);
        }
    }
}

bool insert_into_tree(Tree *t, char *word) {
    if (findNode(t->root, word) == NULL) { // The word is not in the tree
        insertNode(t->root, word);

        return TRUE;
    } else { // The word is already in the tree
        return FALSE;
    }
}

void printPreOrder(Node *node) {
    // ROOT - LEFT - RIGHT
    if (node == NULL) {
        return;
    } else {
        printf("%s\n", node->data);
        printPreOrder(node->left);
        printPreOrder(node->right);
    }

}

void printPostOrder(Node *node) {
    // LEFT - RIGHT - ROOT
    if (node == NULL){
        return;
    } else {
        printPostOrder(node->left);
        printPostOrder(node->right);
        printf("%s\n", node->data);
    }
}


void printInOrder(Node *node) {
    //LEFT - ROOT - RIGHT
    if (node == NULL) {
        return;
    } else {
        printInOrder(node->left);
        printf("%s\n", node->data);
        printInOrder(node->right);
    }
}


char *find_in_tree(Tree *t, char *word) {

    Node *elem = findNode(t->root, word);
    return &elem->data;
}

Node* deleteNode(Node *root, char *word) {

}

int size_tree(Tree *t) {
    printf("Printing size...\n");
    return t->size;
}

void print_tree(Tree *t) {
    printInOrder(t->root);
}

