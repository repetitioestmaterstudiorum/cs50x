#include <stdio.h>
#include <cs50.h>
#include <ctype.h>

// ---

typedef struct
{
    string name;
    string phone;
}
person;

int main(void)
{
    person people[1];

    people[0].name = "gdog";
    people[0].phone = "0123392";

    printf("%s: %s\n", people[0].name, people[0].phone);

    return 0; // good exit code
}

// compile and run: clang -lcs50 ./typedef-struct.c -o typedef-struct.out && ./typedef-struct.out
