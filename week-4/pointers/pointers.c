#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>

// ---

void print_space(void);

int main(void)
{
    char *s = "Hello!";
    // print the starting memory location of a string
    // s is the same as &s[0] because *s is just a pointer to the first char of the string
    printf("%s ..is stored in memory location %p onwards\n", s, s); // Hello! ..
    printf("%s ..is stored in memory location %p onwards\n", &s[0], &s[0]); // Hello! ..

    // print a single char and it's memory location
    printf("%c .. is stored in memory location %p\n", s[1], &s[1]); // e

    // print a string from its 2nd char
    printf("%s ..is stored in memory location %p onwards\n", &s[1], &s[1]); // ello! ..

    // print the ascii of a char
    printf("%i ..is ascii for %c\n", s[1], s[1]); // 101 ..

    // pointer arithmetic
    printf("*s + 1 = %c\n", *s); // H
    printf("*s + 1 = %c\n", *(s + 1)); // e -> same as s[1]

    print_space(); // ---

    // pointer arithmetics on an array of integers
    int numbas[] = {0, 2, 11, 238};
    printf("%i\n", *numbas); // 0
    printf("%i\n", *(numbas + 1)); // 2
    printf("%i\n", *(numbas + 2)); // 11
    printf("%i\n", *(numbas + 3)); // 238

    print_space(); // ---

    // comparing strings and strings from get_string()
    char *str_1 = "This is a string!";
    char *str_2 = "This is a string!";
    printf("str_1: %s, str_2: %s\n", str_1, str_2);
    printf("str_1 address: %p, str_2 address: %p\n", &str_1, &str_2);
    printf("str_1 == str_2: %d\n", str_1 == str_2);
    if (str_1 == str_2)
    {
        printf("the same!\n");
    }
    else
    {
        printf("not the same!\n");
    }
    printf("strcmp(str_1, str_2) == 0: %d\n", strcmp(str_1, str_2) == 0);
    char *fdsa = get_string("fdsa: ");
    char *jklö = get_string("jklö: ");
    printf("fdsa: %s, jklö: %s\n", fdsa, jklö);
    printf("fdsa address: %p, jklö address: %p\n", &fdsa, &jklö);
    printf("fdsa == jklö: %d\n", fdsa == jklö);
    printf("strcmp(fdsa, jklö) == 0: %d\n", strcmp(fdsa, jklö) == 0);
    // -> comparing to same self-typed strings returns true, with get_string false
    // why is str_1 == str_2 when it shouldn't (comparing pointers that aren't the same)?

    print_space(); // ---

    // comparing numbers and numbers from get_int()
    int x = 50;
    int y = 50;
    printf("x: %i, y: %i\n", x, y);
    printf("x == y: %d\n", x == y);

    int i = get_int("i: ");
    int k = get_int("k: ");
    printf("i == k: %d\n", i == k);
    // -> comparing same ints generally returns true
    
    print_space(); // ---

    // malloc and free for copying values assigned to variables safely (clone)
    char *source = "profound words.";
    char *destination = malloc(strlen(source) + 1); // length of source plus 1 for \0 character
    if (destination == NULL)
    {
        return 1; // problem allocating memory
    }
    strcpy(destination, source);
    printf("init: source: %s, destination: %s\n", source, destination);
    printf("source memory: %p, destination memory: %p\n", &source, &destination);
    if (strlen(destination) > 0)
    {
        printf("uppercasing first letter of variable 'destination'\n");
        destination[0] = toupper(destination[0]);
    }
    free(destination); // if executed, will scramble destination contents ... why?
    printf("then: source: %s, destination: %s\n", source, destination);
    printf("source memory: %p, destination memory: %p\n", &source, &destination);

    print_space(); // ---

    // allocate space for ints system-independent (ints can  be of various size dep. on the system)
    int *super_pointer = malloc(sizeof(int));
    *super_pointer = 32;
    int *another_p = super_pointer;
    *another_p = 1;
    printf("super_pointer: %i; another_p: %i\n", *super_pointer, *another_p);

    print_space(); // ---
}

void print_space(void)
{
    printf("\n---\n\n");
}

// compile and run: clang -lcs50 ./pointers.c -o pointers.out && ./pointers.out
