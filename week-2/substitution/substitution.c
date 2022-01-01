#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// ---

/* 
Let’s write a program called substitution that enables you to encrypt messages using a substitution cipher. At the time the user executes the program, they should decide, by providing a command-line argument, on what the key should be in the secret message they’ll provide at runtime.

For example, if the user inputs a key of YTNSHKVEFXRBAUQZCLWDMIPGJO and a plaintext of HELLO:
$ ./substitution VCHPRZGJNTLSKFBDQWAXEUYMOI
plaintext:  hello, world
ciphertext: jrssb, ybwsp

- Your program must accept a single command-line argument, the key to use for the substitution. The key itself should be case-insensitive, so whether any character in the key is uppercase or lowercase should not affect the behavior of your program.
- If your program is executed without any command-line arguments or with more than one command-line argument, your program should print an error message of your choice (with printf) and return from main a value of 1 (which tends to signify an error) immediately.
- If the key is invalid (as by not containing 26 characters, containing any character that is not an alphabetic character, or not containing each letter exactly once), your program should print an error message of your choice (with printf) and return from main a value of 1 immediately.
- Your program must output plaintext: (without a newline) and then prompt the user for a string of plaintext (using get_string).
- Your program must output ciphertext: (without a newline) followed by the plaintext’s corresponding ciphertext, with each alphabetical character in the plaintext substituted for the corresponding character in the ciphertext; non-alphabetical characters should be outputted unchanged.
- Your program must preserve case: capitalized letters must remain capitalized letters; lowercase letters must remain lowercase letters.
After outputting ciphertext, you should print a newline. Your program should then exit by returning 0 from main.
*/

int main(int argc, string argv[])
{
    // # executable argument validation and extraction
    // ## exactly 2 arguments are provided to the executable
    if (argc != 2) // (1st arg = file name, 2nd arg = cipher)
    {
        printf("Usage: ./substitution key\n");
        return 1; // error exit code
    }

    string cipher = argv[1];

    // ## cipher must be 26 characters long
    if (strlen(cipher) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1; // error exit code
    }

    // ## all characters must be alphabetical & key must contain each letter exactly once
    for (int i = 0, n = strlen(cipher); i < n; i++)
    {
        if (isalpha(cipher[i]))
        {
            int c_occurences_in_cipher = 0;
            for (int y = 0; y < n; y++)
            {
                if (tolower(cipher[i]) == tolower(cipher[y]))
                {
                    c_occurences_in_cipher++;
                }
            }
            if (c_occurences_in_cipher > 1)
            {
                printf("Key must contain each letter exactly once.\n");
                return 1; // error exit code
            }
        }
        else
        {
            printf("Key must be alphabetical.\n");
            return 1; // error exit code
        }
    }

    // # get plaintext, transform to ciphertext, print
    string plaintext = get_string("plaintext: ");

    string get_ciphertext(string cipher, string plaintext);
    string ciphertext = get_ciphertext(cipher, plaintext);

    printf("ciphertext: %s\n", ciphertext);

    return 0; // good exit code
}

string get_ciphertext(string cipher, string plaintext)
{
    // clone plaintext to a new variable ciphertext to have non-alphabetic chars unchanged already
    // using malloc and strcpy to avoid mutation (potential unneeded early optimization)
    // this leaves the plaintext unchanged in memory (could be less safe)
    string ciphertext = malloc(strlen(plaintext) + 1);
    strcpy(ciphertext, plaintext);

    // for each alphabetic char in plaintext, get case-adjusted substitute from cipher
    for (int i = 0, n = strlen(ciphertext); i < n; i++)
    {
        if (isalpha(plaintext[i]))
        {
            bool is_upper = isupper(plaintext[i]);
            char c = cipher[(toupper(plaintext[i]) - 65)]; // A = 65 in ascii, 0 = first cipher char
            ciphertext[i] = is_upper ? toupper(c) : tolower(c);
        }
    }

    return ciphertext;
}

/*
compile and run: clang -lcs50 ./substitution.c -o substitution.out && ./substitution.out
check: check50 cs50/problems/2022/x/substitution
submit: submit50 cs50/problems/2022/x/substitution
*/