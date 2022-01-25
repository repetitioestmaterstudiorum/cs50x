#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ---

// type node for binary search tree
typedef struct node
{
    int number;
    struct node *left;
    struct node *right;
}
node;

void print_tree(node *root);
bool search(node *tree, int number);
void free_tree(node *root);

int main(void)
{
    // initiate an empty binary search tree
    node *tree = NULL;

    // // add a number to the tree
    node *n = malloc(sizeof(node)); // get some memory, temporarily
    if (n == NULL) // could not allocate memory
    {
        return 1;
    }
    n->number = 2; // same as (*n).number = 2
    n->left = NULL; 
    n->right = NULL; 
    tree = n; // assign tree to tree in address n

    // add anotaher number to the tree
    n = malloc(sizeof(node)); // get more memory, for another node
    if (n == NULL)
    {
        free(tree); // in case no memory received, free memory before returning from the program
        return 1;
    }
    n->number = 1; // next value in the tree
    n->left = NULL;
    n->left = NULL;
    tree->left = n; // initial tree's left vector should point to this new node (left because 1 < 2)

    // add anotaher number to the tree #2
    n = malloc(sizeof(node)); // get more memory, for another node
    if (n == NULL)
    {
        free(tree);
        return 1;
    }
    n->number = 3; // next value in the tree
    n->left = NULL;
    n->left = NULL;
    tree->right = n; // initial tree's right vector should point to this new node

    print_tree(tree); // 1 2 3

    printf("search 2: %s\n", search(tree, 2) == true ? "found" : "not found");
    printf("search 5: %s\n", search(tree, 5) == true ? "found" : "not found");

    free_tree(tree);

    return 0;
}

void print_tree(node *root)
{
    if (root == NULL)
    {
        return;
    }
    // recursion here
    print_tree(root->left); // first go as left as possible in the tree
    printf("%i\n", root->number); // print the leftest number
    print_tree(root->right); // print number one to the right
}

bool search(node *tree, int number)
{
    if (tree == NULL)
    {
        return false;
    }
    else if (number < tree->number)
    {
        return search(tree->left, number);
    }
    else if (number > tree->number)
    {
        return search(tree->right, number);
    }
    // else if (number == tree->number)
    // {
    //     return true;
    // }
    else
    {
        return true;
    }
}

void free_tree(node *root)
{
    if (root == NULL)
    {
        return;
    }
    // recursion here
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

// compile and run: clang ./binary-search.c -o binary-search.out && ./binary-search.out