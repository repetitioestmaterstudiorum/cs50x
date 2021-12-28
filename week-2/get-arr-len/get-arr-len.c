#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    string str = get_string("enter a word: ");
    
    void print_each_string_char(string str);
    print_each_string_char(str);

    return 0; // main needs to return this
}

void print_each_string_char(string str)
{
    // for (int i = 0; str[i] != '\n'; i++)
    for (int i = 0, str_len = strlen(str); i < str_len; i++)
    {
        printf("char at string position %i: %c\n", i, str[i]);
    }
}