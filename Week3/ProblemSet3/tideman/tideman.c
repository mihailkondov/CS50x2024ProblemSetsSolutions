#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

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
bool _validate_pair(int root_winner, pair node, int pairs_breakpoint);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
// The array ranks[] expresses:
// the index of the most preferred candidate at position 0;
// the index of the second most preferred candidate at position 1;
// and so on...
// where the index of the candidate is decided by the order of entrance in the race
bool vote(int rank, string name, int ranks[])
{
    // check if name is valid:
    bool invalid_name = true;
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++) // Traverse over ranks
    {
        for (int j = 0; j < candidate_count; j++) // traverse again to compare each
                                                  // rank's values with each other
        {
            if (i < j) // rank of one voter lower than the other means they are preferred
            {
                // ranks[i] means index of i-th most preferred candidate (for i = 0 => Alice)
                // that's why I use it in the preferences

                // increment number of voters who prefer Alice[i=0] over Bob[j=1]:
                preferences[ranks[i]][ranks[j]]++;
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            pair current;
            if (preferences[i][j] > preferences[j][i])
            {
                current.winner = i;
                current.loser = j;
                pairs[pair_count] = current;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0; i < pair_count - 1; i++) // for each pair
    {
        for (int j = i + 1; j < pair_count; j++) // compare with each pair (without repeating)
        {
            // preferences[pairs[i].winner][pairs[i].loser] <- i-th pair's victory strength
            if (preferences[pairs[i].winner][pairs[i].loser] <
                preferences[pairs[j].winner][pairs[j].loser])
            {
                // j has stronger victory than i
                // switch places
                pair tmp = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = tmp;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++) // for each pair
    {
        bool is_valid = _validate_pair(pairs[i].winner, pairs[i], i);
        if (is_valid)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        int result = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            result += locked[j][i];
        }
        if (result == 0)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}

// This is a helper function I added myself that checks whether locking a node
// from the list of pairs will create a circular graph.
// returns true if it's ok to lock the pair
// returns false if locking the pair will result in circular graph.
bool _validate_pair(int root_winner, pair node, int pairs_breakpoint)
{
    if (node.loser == root_winner)
    {
        return false;
    }

    for (int i = 0; i < pairs_breakpoint; i++)
    {
        pair next = pairs[i]; // Here I need to check whether the pair was locked or not.
                              // If it was not locked I need to skip it.
        if (locked[next.winner][next.loser] && next.winner == node.loser)
        {
            if (!_validate_pair(root_winner, next, pairs_breakpoint))
            {
                return false;
            }
        }
    }
    return true;
}