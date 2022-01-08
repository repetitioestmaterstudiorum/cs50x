#include <cs50.h>
#include <stdio.h>
#include <string.h>

// ---

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // check if name is in candidates array
    bool is_name_in_candidates = false;
    int candidate_index;
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            is_name_in_candidates = true;
            candidate_index = i;
            break; // no need to look further
        }
    }

    if (is_name_in_candidates)
    {
        candidates[candidate_index].votes += 1;
        return true;
    }
    else
    {
        printf("Provided name is no candidate. ");
        return false;
    }
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // go through candidates array, find candidate with highest votes
    candidate top_candidate = candidates[0];
    int top_candidates_count = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > top_candidate.votes)
        {
            top_candidate = candidates[i];
            top_candidates_count = 1;
        }
        else if (candidates[i].votes == top_candidate.votes)
        {
            top_candidates_count += 1;
        }
    }

    // collect all candidates with the same amount of votes as the top candidate
    candidate winners[top_candidates_count];
    int winners_i = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == top_candidate.votes)
        {
            winners[winners_i] = candidates[i];
            winners_i += 1;
        }
    }

    // print each winner
    for (int i = 0; i < top_candidates_count; i++)
    {
        printf("%s\n", winners[i].name);
    }
    return;
}

/*
compile and run: clang -lcs50 ./plurality.c -o plurality.out && ./plurality.out
check: check50 cs50/problems/2022/x/plurality
submit: submit50 cs50/problems/2022/x/plurality
*/