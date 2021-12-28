#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
// #include <math.h>

/* 

*/

const bool logging = false;

int main(int argc, string argv[])
{
    // executable argument validation and extraction
    if (argc != 2) // only valid amount of arguments (1st arg = file name, 2nd arg = cipher)
    {
        return printf("Usage: ./substitution key\n");
    }
    if (strlen(argv[1]) != 26) // cipher must be 26 characters long
    {
        return printf("Key must contain 26 characters.\n");
    }

    string cipher = argv[1];
    string plaintext = get_string("plaintext: ");

    string get_cipher_text(string text);
    string ciphertext = get_cipher_text(cipher);

    return 0; // good exit code
}

string get_cipher_text(string text)
{
    // int letters = 0;
    // for (int i = 0, n = strlen(text); i < n; i++)
    // {
    //     if (isalpha(text[i]))
    //     {
    //         letters++;
    //     }
    // }
    return "hi";
}

/*
compile and run: clang -lcs50 ./substitution.c -o substitution && ./substitution
check: check50 cs50/problems/2021/x/substitution
submit: submit50 cs50/problems/2021/x/substitution
*/