#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("What's your name?\n");
    printf("hello, %s", name);
}

// compile and run it: "gcc -lcs50 ./hello.c -o hello && ./hello"
// check it: check50 cs50/problems/2021/x/hello
// submit it: submit50 cs50/problems/2021/x/hello