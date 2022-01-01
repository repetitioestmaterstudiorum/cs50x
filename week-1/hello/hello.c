#include <stdio.h>
#include <cs50.h>

// ---

int main(void)
{
    string name = get_string("What's your name?\n");
    printf("hello, %s", name);
}

// compile and run it: "clang -lcs50 ./hello.c -o hello.out && ./hello.out"
// check it: check50 cs50/problems/2022/x/hello
// submit it: submit50 cs50/problems/2022/x/hello