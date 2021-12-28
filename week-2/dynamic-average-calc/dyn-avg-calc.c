#include <stdio.h>
#include <cs50.h>

int main(void)
{
    void print_avg_grade(void);
    print_avg_grade();
    return 0; // main needs to return this
}

void print_avg_grade(void)
{
    const int TOTAL = get_int("How many grades are there in total? ");

    int grades[TOTAL];

    for (int i = 0; i < TOTAL; i++)
    {
        grades[i] = get_int("Enter grade %i: ", i + 1);
    }

    float average(int length, int array[]);
    printf("The average grade is %f\n", average(TOTAL, grades));
}

float average(int length, int array[])
{
    int sum = 0;

    for (int i = 0; i < length; i++)
    {
        sum += array[i];
    }

    return (float) sum / length;
}