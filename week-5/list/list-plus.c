#include <stdio.h>
#include <stdlib.h>

// ---

int main(void)
{
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
    int *temp_list = realloc(list, 4 * sizeof(int)); // no manual copy of values necessary
    if (temp_list == NULL)
    {
        free(list);
        return 1;
    }
    temp_list[3] = 4; // actual extension

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

// compile and run: clang ./list-plus.c -o list-plus.out && ./list-plus.out