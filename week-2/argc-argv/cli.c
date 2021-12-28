#include <stdio.h>
#include <cs50.h>

// argc = amount of arguments passed to the executable
// argv = arguments passed to the executable
int main(int argc, string argv[])
{
    if (argc > 0)
    {
        for (int i = 0; i < argc; i++)
        {
            printf("i: %i, argv[i]: %s\n", i, argv[i]);
        }
    }

    return 0;
}

// clang -lcs50 ./cli.c -o cli && ./cli

/* 
clang -lcs50 ./cli.c -o cli && ./cli hello there =>
i: 0, argv[i]: ./cli
i: 1, argv[i]: hello
i: 2, argv[i]: there
*/

/*
get exit code of last executable that was run:
echo $? => 
0
*/