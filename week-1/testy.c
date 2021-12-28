#include <cs50.h>
#include <stdio.h>

// compile and run it: "gcc -lcs50 ./testy.c -o testy && ./testy"

// announcing that these functions exists further below
void print_numbers_from_to(int from, int to);
int get_positive_int(void);

int main(void)
{
    // function calls
    print_numbers_from_to(0, 3);

    // plus variable assignment
    int i = get_positive_int();
    printf("the entered positive integer is: %i\n", i);

    // loops
    int incremental_variable = 0;
    while (incremental_variable < 4)
    {
        printf("while incremental_variable is %i\n", incremental_variable);
        incremental_variable++;
    }

    for (int incremental_variable = 0; incremental_variable < 5; incremental_variable++)
    {
        printf("for incremental_variable is %i\n", incremental_variable);
    }

    // addition
    int x = get_int("x: ");
    long y = get_long("y: ");
    long addition_result = x + y;

    printf("x plus y is %li\n", addition_result);

    // condition
    if (x > y)
    {
        printf("x is larger than y");
    }
    else if (y > x)
    {
        printf("y is larger than x");
    }
    else
    {
        printf("x and y are equal");
    }

    // division
    int divisor = get_int("divisor: ");

    float division_result = (float) addition_result / divisor;

    printf("%li divided by %i is %f\n", addition_result, divisor, division_result);

    // char comparison
    char c = get_char("Do you agree? ");

    if (c == 'y' || c == 'Y')
    {
        printf("Good.\n");
    }
    else
    {
        printf("Well, we got a problem then.\n");
    }
}

// function that retruns nothing
void print_numbers_from_to(int from, int to)
{
    printf("from %i to %i\n", from, to);
    for (int i = from; i < to; i++)
    {
        printf("i is %i\n", i);
    }
}

// function that returns an int
int get_positive_int(void)
{
    int n;
    do
    {
        n = get_int("Positive Integer: ");
    }
    while (n < 1);
    return n;
}
