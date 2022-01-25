#include <stdio.h>
#include <stdlib.h>

// ---

// type node for linked list
typedef struct node
{
    int number;
    struct node *next;
}
node;

int main(void)
{
    // initiate an empty linked list
    node *list = NULL;

    // add a number to the list
    node *n = malloc(sizeof(node)); // get some memory, temporarily
    if (n == NULL) // could not allocate memory
    {
        return 1;
    }
    n->number = 1; // same as (*n).number = 1 (i.e.: go to address of n and set its number to 1)
    n->next = NULL; // same as (*n).next = NULL
    list = n; // assign list to list in address n

    // add anotaher number to the list
    n = malloc(sizeof(node)); // get more memory, for another node
    if (n == NULL)
    {
        free(list); // in case no memory received, free memory before returning from the program
        return 1;
    }
    n->number = 2; // next value in the list
    n->next = NULL; // next node points nowhere
    list->next = n; // existing list (first node) points to 2nd node

    // add another numebr to the list #2
    n = malloc(sizeof(node));
    if (n == NULL)
    {
        free(list->next); // free node 2 (needs to happen first, before clearing 1)
        free(list); // free node 1
        return 1;
    }
    n->number = 3;
    n->next = NULL;
    list->next->next = n;

    // print list contents
    printf("list->number: %i\n", list->number); // 1
    printf("list->next->number: %i\n", list->next->number); // 2
    printf("list->next->next->number: %i\n", list->next->next->number); // 3

    // print entire list
    printf("list: ");
    // point tmp to node 1; as long as tmp doesn't point to NULL; assign tmp to the next node
    for (node *tmp = list; tmp != NULL; tmp = tmp->next)
    {
        if (tmp != list) // only after first iteration
        {
            printf(", ");
        }
        // print current node's number, where tmp is pointing to in this iteration
        printf("%i", tmp->number);
    }
    printf("\n");

    // free entire linked list
    while (list != NULL)
    {
        node *tmp = list->next; // find 2nd node
        free(list); // free first node
        list = tmp; // assign list node 2, repeat cycle
    }

    return 0;
}

// compile and run: clang ./linked-list.c -o linked-list.out && ./linked-list.out