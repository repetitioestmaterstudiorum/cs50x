#include <cs50.h>
#include <stdio.h>

// ---

void print_blocks(int length);

int main(void)
{
    /* declare needed variable(s) */
    int height;
    
    /* ask for the height until the entered integer is between 1 and 8 */
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    /* print pyramid */
    for (int i = 1; i <= height; i++)
    {
        /* print white space if needed */
        for (int width = height - i; width > 0; width--)
        {
            printf(" ");
        }
        /* print blocks on the left */
        print_blocks(i);

        /* print gap */
        printf("  ");
        
        /* print blocks on the right */
        print_blocks(i);

        /* line break */
        printf("\n");
    }
}

void print_blocks(int length)
{
    for (int width = 0 ; width < length ; width++)
    {
        printf("#");
    }
}

/* 
compile and run it: "clang -lcs50 ./mario.c -o mario.out && ./mario.out"
check it: check50 cs50/problems/2022/x/mario/more
submit it: submit50 cs50/problems/2022/x/mario/more
*/