#include <stdio.h>
#include <stdlib.h>

// ---

int main(void)
{
    // fixed list of 3, can't change size or free memory -> not very gud
    // int list[3];

    // list with malloc we can free
    int *list = malloc(3 * sizeof(int));
    if (list == NULL)
    {
        return 1;
    }
    list[0] = 1;
    list[1] = 2;
    list[2] = 3;

    // temporary list to extend existing list
    int *temp_list = malloc(4 * sizeof(int));
    if (temp_list == NULL)
    {
        free(list);
        return 1;
    }
    // manual copy of list values to temp_list
    for (int i = 0; i < 3; i++)
    {
        temp_list[i] = list[i];
    }
    temp_list[3] = 4; // actual extension

    free(list); // free previous list's memory

    list = temp_list; // assign list to temporary list's new memory

    // use the list
    for (int i = 0; i < 4; i++)
    {
        printf("%i\n", list[i]);
    }
    // free list's memory after usage
    free(list);

    return 0; // good exit code
}

// compile and run: clang ./list.c -o list.out && ./list.out