#include <cs50.h>
#include <stdio.h>
#include <string.h>

// ---

/* Tally: Once all of the voters have indicated all of their preferences, determine, for each pair of candidates, who the preferred candidate is and by what margin they are preferred.

Sort: Sort the pairs of candidates in decreasing order of strength of victory, where strength of victory is defined to be the number of voters who prefer the preferred candidate.

Lock: Starting with the strongest pair, go through the pairs of candidates in order and “lock in” each pair to the candidate graph, so long as locking in that pair does not create a cycle in the graph. */

const bool LOG = true;

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];
bool cycle = false;
int locked_count;

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
    int won_by;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        LOG &&printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        LOG &&printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                LOG &&printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        LOG &&printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
// ranks[i] represents the user’s ith preference
bool vote(int rank, string name, int ranks[])
{
    // check if name is in candidates array, and if so, find candidate's index
    int candidate_index = -1;
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            candidate_index = i;
            break;
        }
    }

    // record rank and candidate's index in ranks array
    if (candidate_index > -1)
    {
        ranks[rank] = candidate_index;
        return true;
    }
    else
    {
        LOG &&printf("Provided name is no candidate.\n");
        return false;
    }
}

// Update preferences given one voter's ranks
// preferences[i][j] represents the number of voters who prefer candidate i over candidate j.
void record_preferences(int ranks[])
{
    LOG &&printf("ranks[0]: %i, ranks[1]: %i, ranks[2]: %i\n", ranks[0], ranks[1], ranks[2]);
    /* example candidates: thomas, matt, sali
    example choice:     1: matt, 2: sali, 3: thomas -> ranks[0]: 1, ranks[1]: 2, ranks[2]: 0
    ranks[0] ranks[1] -> matt sali -> 1, 2: 1 -> preferences[1][2] += 1
    ranks[0] ranks[2] -> matt thom -> 1, 0: 1 -> preferences[1][0] += 1
    ranks[1] ranks[2] -> sali thom -> 2, 0: 1 -> preferences[2][0] += 1 */
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] += 1;
        }
    }
    LOG &&printf("[0][1]: %i, [0][2]: %i, [1][0]: %i, [2][0]: %i, [2][1]: %i, [1][2]: %i\n", preferences[0][1], preferences[0][2], preferences[1][0], preferences[2][0], preferences[2][1], preferences[1][2]); 
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            int i_minus_j = preferences[i][j] - preferences[j][i];
            if (i_minus_j != 0) // either i or j has more votes and won
            {
                int smth = i_minus_j > 0 ? i : j;
                pairs[pair_count].winner = i_minus_j > 0 ? i : j; // i won over j
                pairs[pair_count].loser = i_minus_j > 0 ? j : i; // j won over j
                pairs[pair_count].won_by = i_minus_j > 0 ? i_minus_j : i_minus_j * -1;
                pair_count += 1;
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory (assume equal won_by order doesn't matter)
void sort_pairs(void)
{
    // selection sort: order descendingly
    int highest_won_by;
    pair swap;
    for (int i = 0; i < pair_count - 1; i++)
    {
        highest_won_by = i;
        for (int j = i + 1; j < pair_count; j++)
        {
            if (pairs[j].won_by > pairs[highest_won_by].won_by)
            {
                highest_won_by = j;
            }
        }
        if(highest_won_by != i)
        {
            swap = pairs[i];
            pairs[i] = pairs[highest_won_by];
            pairs[highest_won_by] = swap;
        }
    }

    LOG &&printf("pair_count: %i\n", pair_count);
    for (int i = 0; i < pair_count; i++)
    {
        LOG &&printf("pair %i - w: %s, l: %s, won_by: %i\n", i, candidates[pairs[i].winner], candidates[pairs[i].loser], pairs[i].won_by);
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
// locked[i][j] means i is locked in over j
void lock_pairs(void)
{
    /* example pairs after sorting (thomas matt sali):
    pair 0 - w: thomas, l: sali, won_by: 3
    pair 1 - w: matt, l: sali, won_by: 3
    pair 2 - w: matt, l: thomas, won_by: 1

    graph 1: thomas over sali ->    locked[candidates[thomas]][candidates[sali]  -> locked[0][2]
    graph 2: matt over sali ->      locked[candidates[matt]][candidates[sali]    -> locked[1][2]
    graph 3: matt over thomas ->    locked[candidates[matt]][candidates[thomas]  -> locked[1][0]
    bad graph would be: locked[2][1] */

    void recurse_creates_cycle(int forbidden_src, int src[], int src_len); 

    for (int i = 0; i < pair_count; i++)
    {
        LOG &&printf("pairs[i].winner: %i\n", pairs[i].winner);
        int loser_as_array[] = {pairs[i].loser};

        recurse_creates_cycle(pairs[i].winner, loser_as_array, 1);

        if (!cycle)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
            locked_count += 1;
            LOG &&printf("created locked pair [%i][%i]\n", pairs[i].winner, pairs[i].loser);
        }
    }
    LOG &&printf("\n");
    LOG &&printf("locked[0][1]: %i\n", locked[0][1]);
    LOG &&printf("locked[0][2]: %i\n", locked[0][2]);
    LOG &&printf("locked[1][0]: %i\n", locked[1][0]);
    LOG &&printf("locked[1][2]: %i\n", locked[1][2]);
    LOG &&printf("locked[2][0]: %i\n", locked[2][0]);
    LOG &&printf("locked[2][1]: %i\n", locked[2][1]);
}

// Print the winner of the election
void print_winner(void)
{
    /* example locked matrix (2D array):
    locked[0][1]: true                  0   1   2
    locked[0][2]: false     thomas  0       t
    locked[1][0]: false     matt    1     
    locked[1][2]: false     sali    2   t
    locked[2][0]: true
    locked[2][1]: false
    winner = no arrows point to candidate -> 2: sali */

    int winner;
    int potential_winners[candidate_count];
    int potential_winners_count = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        for (int y = 0; y < candidate_count; y++)
        {
            if (locked[i][y] == true)
            {
                potential_winners[potential_winners_count] = i;
                potential_winners_count += 1;
            }
        }
    }

    for (int i = 0; i < potential_winners_count; i++)
    {
        int curr = potential_winners[i];
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][curr])
            {
                continue;
            }
            else
            {
                winner = curr;
                break;
            }
        }
    }

    LOG &&printf("\n");
    printf("%s\n", candidates[winner]);
}

// helper function(s)
void recurse_creates_cycle(int forbidden_src, int src[], int src_len)
{
    LOG &&printf(" -- cycle: ");
    LOG &&printf("forbidden_src: %i, src[]: [%i], src_len: %i)\n", forbidden_src, src[0], src_len);

    int next_src_len = 0;
    int next_src[locked_count];

    for (int i = 0; i < src_len; i++)
    {
        LOG &&printf("loop: i: %i\n", i);
        int curr = src[i];
        if (locked[curr][forbidden_src] == true)
        {
            /*
            create cycle: 
            voter 1: matt, sali, thomas
            voter 2: sali, thomas, matt
            voter 3: thomas, matt, sali
            locked: [0][1] and [2][0], cycle (not locked in): [1][2]
            */
            LOG &&printf("CYCLE!\n");
            cycle = true;
            break;
        }
        else
        {
            for (int y = 0; y < candidate_count; y++)
            {
                if (locked[curr][y] == true)
                {
                    next_src[next_src_len] = y;
                    next_src_len += 1;
                }
            }
        }
    }

    LOG &&printf("next_src_len: %i, cycle: %d\n", next_src_len, cycle);
    if (next_src_len > 0)
    {
        recurse_creates_cycle(forbidden_src, next_src, next_src_len);
    }
}

/*
compile and run: clang -lcs50 ./tideman.c -o tideman.out && ./tideman.out
check: check50 cs50/problems/2022/x/tideman
submit: submit50 cs50/problems/2022/x/tideman
*/

/* check50
:) tideman.c exists
:) tideman compiles
:) vote returns true when given name of candidate
:) vote returns false when given name of invalid candidate
:) vote correctly sets rank for first preference
:) vote correctly sets rank for all preferences
:) record_preferences correctly sets preferences for first voter
:) record_preferences correctly sets preferences for all voters
:) add_pairs generates correct pair count when no ties
:) add_pairs generates correct pair count when ties exist
:) add_pairs fills pairs array with winning pairs
:) add_pairs does not fill pairs array with losing pairs
-> :( sort_pairs sorts pairs of candidates by margin of victory
    sort_pairs did not correctly sort pairs
    -> can't reproduce. maybe because added won_by to struct, which was provided by cs50x
:) lock_pairs locks all pairs when no cycles
:) lock_pairs skips final pair if it creates cycle
-> :( lock_pairs skips middle pair if it creates a cycle
    lock_pairs did not correctly lock all non-cyclical pairs
    -> can't reproduce!
-> :( print_winner prints winner of election when one candidate wins over all others
    print_winner did not print winner of election
    -> can't reproduce!
:) print_winner prints winner of election when some pairs are tied
*/