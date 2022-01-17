#include <stdio.h>
#include <stdlib.h>

// ---

void swap(int *a, int *b);

int main(void)
{
    int x = 1;
    int y = 2;
    printf("x: %i, y: %i\n", x, y);
    swap(&x, &y);
    printf("x: %i, y: %i\n", x, y);
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// compile and run: clang -lcs50 ./swap.c -o swap.out && ./swap.out
