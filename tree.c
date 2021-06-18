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
    if (node == NULL || (node->left == 0 && node->right == 0)) {
       free(node);
    }

    // Recursive Case
    else {
       // Delete the whole left branch
       if (node->left != NULL) {
           clearPostOrder(node->left);
       }
       // Delete the whole right branch
       if (node->right != NULL) {
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
            node->right = insertNode(node->right, word);
        } else if (strcmp(word, node->data) < 0) { // Element we want to insert is lower than the current root of the subtree (word < node->data)
            node->left = insertNode(node->left, word);
        }
    }

    return node;
}

Node *findNode(Node *node, char *word) {
    if (node == NULL) { // Base case 1: the node is not found.
        return NULL;
    } else {
        if (strcmp(word, node->data) == 0) { // Base case 2: We find the node
            return node;
        }
        // Recursive case:
        else if (strcmp(word, node->data) > 0) {
            return findNode(node->right, word);
        } else {
            return findNode(node->left, word);
        }
    }
}

bool insert_into_tree(Tree *t, char *word) {
    if (findNode(t->root, word) == NULL) { // The word is not in the tree
        t->root = insertNode(t->root, word);
        t->size++;

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
    return elem->data;
}

char* get_max(Node **root) {
    if ((*root)->right != NULL){
        return get_max(&(*root)->right);
    } else {
        int length_data = strlen((*root)->data);
        char *word = malloc(length_data * sizeof(char));
        strcpy(word, (*root)->data);

        // Reordering the tree and freeing the node that has to be deleted
        Node *tmp = (*root);
        (*root) = (*root)->left;
        free(tmp);

        return word;
    }
}


Node* deleteNode(Node *root, char *word) {
    if (root == NULL) {
        return NULL;
    } else {
        if (strcmp(word, root->data) > 0) {
            root->right = deleteNode(root->right, word);
        } else if (strcmp(word, root->data) < 0)  {
            root->left = deleteNode(root->left, word);
        } else {
            Node* tmp = root;
            // The case where node is a leaf is implicit in these two conditions
            if (root->right == NULL) { // The node only has a left subtree
                root = root->left;
                free(tmp);
            } else if (root->left == NULL) { // The node only has a right subtree
                root = root->right;
                free(tmp);
            } else {
                // Use auxiliary function
                char *new_data = get_max(&root->left);
                strcpy(root->data, new_data);
                free(new_data);

            }
        }
        return root;
    }
}


int size_tree(Tree *t) {
    printf("Printing size...\n");
    return t->size;
}

void print_tree(Tree *t) {
    printInOrder(t->root);
}

