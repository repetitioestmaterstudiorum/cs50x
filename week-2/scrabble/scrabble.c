#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

// ---

/* In the game of Scrabble, players create words to score points, and the number of points is the sum of the point values of each letter in the word.

0 Points - Blank tile.
1 Point - A, E, I, L, N, O, R, S, T and U.
2 Points - D and G.
3 Points - B, C, M and P.
4 Points - F, H, V, W and Y.
5 Points - K.
8 Points - J and X.
10 Points - Q and Z.

For example, if we wanted to score the word Code, we would note that in general Scrabble rules, the C is worth 3 points, the o is worth 1 point, the d is worth 2 points, and the e is worth 1 point. Summing these, we get that Code is worth 3 + 1 + 2 + 1 = 7 points. */

const bool LOGGING = false;

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int compute_score(string word);
    int score1 = compute_score(word1);
    LOGGING &&printf("score1: %i\n", score1);
    int score2 = compute_score(word2); 
    LOGGING &&printf("score2: %i\n", score2);

    /* In main(), your program should print, depending on the players’ scores, Player 1 wins!, Player 2 wins!, or Tie!. */

    if (score1 == score2)
    {
        printf("Tie!");
    }
    else if (score1 > score2)
    {
        printf("Player 1 wins!");
    }
    else
    {
        printf("Player 2 wins!");
    }
    printf("\n");

    return 0; // good exit code
}

int compute_score(string word)
{
    /* In compute_score(), your program should compute, using the POINTS array, and return the score for the string argument. Characters that are not letters should be given zero points, and uppercase and lowercase letters should be given the same point values.
    For example, ! is worth 0 points while A and a are both worth 1 point.
    Though Scrabble rules normally require that a word be in the dictionary, no need to check for that in this problem! */

    // Points assigned to each letter of the alphabet ({a, b, c, ...})
    const int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

    int points = 0;

    for (int i = 0, n = strlen(word); i < n; i++)
    {
        if (isalpha(word[i])) // no points for non-alpha numeric characters
        {
            char lowered = tolower(word[i]); 
            LOGGING &&printf("input: %c, ascii: %i, arr idx: %i, points: %i\n", lowered, lowered, lowered - 97, POINTS[lowered - 97]);
            points += POINTS[lowered - 97];
        }
        else 
        {
            LOGGING &&printf("not alpha: %c\n", word[i]);
        }
    }

    return points;
}

/*
compile and run: clang -lcs50 ./scrabble.c -o scrabble.out && ./scrabble.out
check: check50 cs50/labs/2022/x/scrabble.out
submit: submit50 cs50/labs/2022/x/scrabble.out
*/