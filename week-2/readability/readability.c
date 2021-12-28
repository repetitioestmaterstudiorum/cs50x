#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

/* 
- Your program should count the number of letters, words, and sentences in the text. You may assume that a letter is any lowercase character from a to z or any uppercase character from A to Z, any sequence of characters separated by spaces should count as a word, and that any occurrence of a period, exclamation point, or question mark indicates the end of a sentence.
- Your program should print as output "Grade X" where X is the grade level computed by the Coleman-Liau formula (index = 0.0588 * L - 0.296 * S - 15.8 [L is the average number of letters per 100 words in the text, and S is the average number of sentences per 100 words in the text]), rounded to the nearest integer.
- If the resulting index number is 16 or higher (equivalent to or greater than a senior undergraduate reading level), your program should output "Grade 16+" instead of giving the exact index number. If the index number is less than 1, your program should output "Before Grade 1".
- Exampls: Text: Congratulations! Today is your day. You're off to Great Places! You're off and away! => Grade 3
*/

const bool logging = false;

int main(void)
{
    string text = get_string("Text: ");

    // counting
    int count_letters(string text);
    int letters = count_letters(text);
    logging && printf("letters: %i\n", letters);

    int count_words(string text);
    int words = count_words(text);
    logging && printf("words: %i\n", words);

    int count_sentences(string text);
    int sentences = count_sentences(text);
    logging && printf("sentences: %i\n", sentences);

    // index calculations
    float avg_letters_100_words = (float) letters / words * 100;
    logging && printf("avg_letters_100_words: %f\n", avg_letters_100_words);
    float avg_sentences_100_words = (float) sentences / words * 100;
    logging && printf("avg_sentences_100_words: %f\n", avg_sentences_100_words);

    float index = 0.0588 * avg_letters_100_words - 0.296 * avg_sentences_100_words - 15.8;
    logging && printf("index: %f\n", index);

    // result interpretation
    if (index > 16)
    {
        printf("Grade 16+");
    }
    else if (index < 1)
    {
        printf("Before Grade 1");
    }
    else
    {
        printf("Grade %i", (int) round(index));
    }
    printf("\n");

    return 0; // good exit code
}

// the following functions could be combined into one  (e.g. count_text_properties), but this would reduce reusability. The perhaps better argument to being lazy and keeping 3 functions is that the code is easier to read.

int count_letters(string text)
{
    int letters = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
    }
    return letters;
}

int count_words(string text)
{
    int words = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == ' ')
        {
            words++;
        }
    }

    words = words ? words + 1 : 0; // if 1+ space exists, add another (1 space means 2 words)

    return words;
}

int count_sentences(string text)
{
    int sentences = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }
    return sentences;
}

/*
compile and run: clang -lcs50 ./readability.c -o readability && ./readability
check: check50 cs50/problems/2021/x/readability
submit: submit50 cs50/problems/2021/x/readability
*/