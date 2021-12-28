#include <cs50.h>
#include <stdio.h>

int get_start_size_larger_than_nine(void);
int get_end_size_larger_than_start(int start_size);

int main(void)
{
    int s = get_start_size_larger_than_nine();
    int e = get_end_size_larger_than_start(s);

    int years = 0;
	
    while (s < e)
    {
        printf(".");
        int new_llamas = s / 3;
        int dead_llamas = s / 4;

        s = s + new_llamas - dead_llamas;

        years++;
    } 
    
    printf("\nYears: %i\n", years);
}

int get_start_size_larger_than_nine(void)
{
    int start_size;
    do
    {
        start_size = get_int("start size: ");
    } 
    while (start_size < 9);
    return start_size;
}

int get_end_size_larger_than_start(int start_size)
{
    int end_size;
    do
    {
        end_size = get_int("end size: ");
    } 
    while (end_size < start_size);
    return end_size;
}

// gcc -lcs50 ./population.c -o population && ./population
