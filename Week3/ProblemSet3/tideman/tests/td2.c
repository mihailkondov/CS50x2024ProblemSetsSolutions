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

const int voter_count = 3;
const int candidate_count = 3;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool validate_pair(int root_winner, pair node, int pairs_breakpoint);

int main(int argc, string argv[]) // This main function is for debugging purposes. The real one is in tideman_main.c
{


    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
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

    printf("Number of voters: %i\n", voter_count);

    string votes[voter_count][candidate_count] =
    {
        {"Alice", "Bob", "Charlie"},
        {"Bob", "Charlie", "Alice"},
        {"Alice", "Bob", "Charlie"},
        // {"Alice", "Charlie", "Bob"},
        // {"Charlie", "Bob", "Alice"},
        // {"Charlie", "Bob", "Alice"},
        // {"Charlie", "Bob", "Alice"},
    };
    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = votes[i][j];
            printf("Rank %i: %s\n", j + 1, name);

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
        for (int j = 0; j < candidate_count; j++) // traverse again to compare each ranks values with each other
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
        for (int j = i + 1; j < candidate_count; j++)
        {
            pair current;
            if (preferences[i][j] > preferences[j][i])
            {
                current.winner = i;
                current.loser = j;
                pairs[pair_count] = current;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                current.winner = j;
                current.loser = i;
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
// DEBUG ------------------------------------------------------------------
    for(int i = 0; i < candidate_count; i++)
    {

        for (int j = 0; j < candidate_count; j++)
        {
            if(preferences[i][j] > preferences[j][i])
            {
                printf("%c > %c: %i-%i\n", 65 + i, 65 + j, preferences[i][j], preferences[j][i]);
            }
        }
    }
    for (int k = 0; k < pair_count; k++)
    {
        printf("pair %i: win-%c, lose-%c; Score: %i\n",
                k,
                65 + pairs[k].winner,
                65 + pairs[k].loser,
                preferences[pairs[k].winner][pairs[k].loser]);
    }
// END DEBUG --------------------------------------------------------------

    for (int i = 0; i < pair_count - 1; i++) // for each pair
    {
        for (int j = i + 1; j < pair_count; j++) // compare with each pair (without repeating)
        {
            // preferences[pairs[i].winner][pairs[i].loser] <- i-th pair's victory strength
            if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[j].winner][pairs[j].loser])
            {
                // j has stronger victory than i
                // switch places
                pair tmp = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = tmp;

                // DEBUG ------------------------------------------------------------------
                printf("Switch happened: %i and %i\n", i, j);
                for (int k = 0; k < pair_count; k++)
                {
                    printf("pair %i: win-%c, lose-%c; Score: %i\n",
                            k,
                            65 + pairs[k].winner,
                            65 + pairs[k].loser,
                            preferences[pairs[k].winner][pairs[k].loser]);
                }
                // END DEBUG --------------------------------------------------------------
            }
        }
    }
    // DEBUG ------------------------------------------------------------------
    for(int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if(preferences[i][j] > preferences[j][i])
            {
                printf("%c > %c: %i-%i\n", 65 + i, 65 + j, preferences[i][j], preferences[j][i]);
            }
        }
    }
    for (int k = 0; k < pair_count; k++)
    {
        printf("pair %i: win-%c, lose-%c; Score: %i-%i\n",
                k,
                65 + pairs[k].winner,
                65 + pairs[k].loser,
                preferences[pairs[k].winner][pairs[k].loser],
                preferences[pairs[k].loser][pairs[k].winner]);
    }
    // END DEBUG --------------------------------------------------------------
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++) // for each pair
    {
        bool is_valid = validate_pair(pairs[i].winner, pairs[i], i);
        if(is_valid)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
// DEBUG ------------------------------------------------------------------
            printf("locked %c > %c\n", 65 + pairs[i].winner, 65 + pairs[i].loser);
// END DEBUG --------------------------------------------------------------
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int votes[candidate_count];
    for (int i = 0; i < candidate_count; i++)
    {
        votes[i] = 0; // This is very important, otherwise I might end up with
                      // a garbage initial value
        for(int j = 0; j < candidate_count; j++)
        {
            printf("%b ", locked[i][j]);
            if(locked[i][j] == true)
            {
                votes[i]++;
            }
        }
        printf("\n");
    }

    int max_votes = 0;
    for(int i = 0; i < candidate_count; i++)
    {
        printf("Votes for %s: %i\n", candidates[i], votes[i]);
        if(votes[i] > max_votes)
        {
            max_votes = votes[i];
            printf("new max: %i for %s\n", max_votes, candidates[i]);
        }
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (votes[i] == max_votes)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}

bool validate_pair(int root_winner, pair node, int pairs_breakpoint)
{
    if(node.loser == root_winner)
    {
        return false;
    }

    for (int i = 0; i < pairs_breakpoint; i++)
    {
        pair next = pairs[i];
        if(next.winner == node.loser)
        {
            if (!validate_pair(root_winner, next, pairs_breakpoint))
            {
                return false;
            }
        }
    }
    return true;
}
