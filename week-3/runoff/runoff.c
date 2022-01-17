#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// ---

// logging (for development purposes)
const bool LOG = false;

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        LOG &&printf("candidates:\n");
        for (int candi = 0; candi < candidate_count; candi++)
        {
            LOG &&printf("name: %s, votes: %i, elim: %d\n", candidates[candi].name, candidates[candi].votes, candidates[candi].eliminated);
        }
        LOG &&printf("\n");

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        LOG &&printf("min: %i\n\n", min);
        bool tie = is_tie(min);
        LOG &&printf("tie (bool): %d\n\n", tie);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // check if name is in candidates array, and if so, find candidate's index
    int candidate_index = -1;
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidate_index = i;
            break;
        }
    }

    // record rank and candidate's index in preferences 2d array
    if (candidate_index > -1)
    {
        preferences[voter][rank] = candidate_index;
        return true;
    }
    else
    {
        printf("Provided name is no candidate.\n");
        return false;
    }
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    LOG &&printf("tabulate:\n");
    for (int voter = 0, choice; voter < voter_count; voter++)
    {
        choice = 0;

        while (candidates[preferences[voter][choice]].eliminated)
        {
            LOG &&printf("(choice++)\n");

            choice += 1;
        }

        LOG &&printf("voter: %i, choice: %i\n", voter, choice);
        LOG &&printf("name: %s, votes: %i, elim: %d\n", candidates[preferences[voter][choice]].name, 
                     candidates[preferences[voter][choice]].votes, candidates[preferences[voter][choice]].eliminated);

        candidates[preferences[voter][choice]].votes += 1;
    }
    LOG &&printf("\n");
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    int required_votes = (int) ceil((voter_count / 2.0) + 0.5); // ceil of +.5 in case uneven
    LOG &&printf("required_votes: %i\n", required_votes);

    int winner_index = -1; // -1 -> not found

    for (int candi = 0; candi < candidate_count; candi++)
    {
        if (candidates[candi].eliminated == false && candidates[candi].votes >= required_votes)
        {
            winner_index = candi;
            break;
        }
    }
    LOG &&printf("winner_index: %i\n\n", winner_index);

    if (winner_index > -1)
    {
        printf("%s\n", candidates[winner_index].name);
        return true;
    }
    else
    {
        return false;
    }
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min;
    for (int candi = 0; candi < candidate_count; candi++)
    {
        if (candidates[candi].eliminated == false)
        {
            min = candidates[candi].votes < min ? candidates[candi].votes : min;
        }
    }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int last_votes = -1;
    bool all_same_votes = true;
    for (int candi = 0; candi < candidate_count; candi++)
    {
        if (candidates[candi].eliminated == false)
        {
            if (last_votes == -1) // add votes of first non-eliminated candidate
            {
                last_votes = candidates[candi].votes;
                continue;
            }
            if (candidates[candi].votes != last_votes) // not a tie
            {
                all_same_votes = false;
                break;
            }
            last_votes = candidates[candi].votes;
        }
    }
    return all_same_votes;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int candi = 0; candi < candidate_count; candi++)
    {
        if (candidates[candi].eliminated == false && candidates[candi].votes == min)
        {
            candidates[candi].eliminated = true;
        }
    }
}

/*
compile and run: clang -lcs50 ./runoff.c -o runoff.out && ./runoff.out
check: check50 cs50/problems/2022/x/runoff
submit: submit50 cs50/problems/2022/x/runoff
*/