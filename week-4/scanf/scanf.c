#include <stdio.h>
#include <stdlib.h>

// ---

int main(void)
{
    // read int
    int x;
    printf("x: ");
    scanf("%i", &x); // get int, put it in pointer location of x
    printf("x: %i\n", x);

    // read string
    char *y = malloc(1);
    printf("y: ");
    scanf("%s", y); // get string, put it in pointer location of y
    printf("y: %s\n", y);
    /*
    this *should* lead to a segmentation fault (however, it just saves only one string
    if more than 1 string is entered)
    */
}


// compile and run: clang -lcs50 ./scanf.c -o scanf.out && ./scanf.out
