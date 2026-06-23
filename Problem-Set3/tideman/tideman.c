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
bool check_cycle(int target, int start);
void print_winner(void);

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

    for (int i = 0; i < candidate_count; i++)
        for (int j = 0; j < candidate_count; j++)
            preferences[i][j] = 0;

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
    // lock_pairs();
    // print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i; // i = candidate number!
            printf("Ranks[%i] = %i\n", rank, i);
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{

    for (int i = 0; i < candidate_count - 1; i++)
    {
        int current_top = ranks[i];
        printf("current_top = %i\n", ranks[i]);
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[current_top][ranks[j]]++;
            printf("preferences[%i][%i] = %i\n", current_top, ranks[j],
                   preferences[current_top][ranks[j]]);
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
            printf("preferences[%i][%i] = %i, preferences[%i][%i] = %i\n", i, j, preferences[i][j],
                   j, i, preferences[j][i]);
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                printf("pair[%i]: winner:%i, loser:%i\n", pair_count, i, j);
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                printf("pair[%i]: winner:%i, loser:%i\n", pair_count, j, i);
                pair_count++;
            }
        }
    }

    // for(int i  = 0; i < pair_count; i++)
    // {
    //     printf("Pair %i: winner: %i, loser: %i\n", i, pairs[i].winner, pairs[i].loser);
    // }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    printf("\nAfter Sorting:\n");
    for (int i = 0; i < pair_count; i++)
    {
        int max = -1;
        int max_pair = -1;
        for (int j = i; j < pair_count; j++)
        {
            int diff = preferences[pairs[j].winner][pairs[j].loser] -
                       preferences[pairs[j].loser][pairs[j].winner];
            // printf("diff: %i, i: %i, j: %i\n", diff, i, j);
            if (diff > max)
            {
                max = diff;
                max_pair = j;
            }
        }
        // printf("max: %i\n", max);
        // swap(pairs[i], pairs[min_pair]);
        // for(int k  = 0; k < pair_count; k++)
        //     printf("Before Swap Pair %i: winner: %i, loser: %i\n", k, pairs[k].winner,
        //     pairs[k].loser);
        pair temp = pairs[i];
        pairs[i] = pairs[max_pair];
        pairs[max_pair] = temp;
        // for(int k = 0; k < pair_count; k++)
        //         printf("After Swap Pair %i: winner: %i, loser: %i\n", k, pairs[k].winner,
        //         pairs[k].loser);
    }

    for (int i = 0; i < pair_count; i++)
        printf("Pair %i: winner: %i, loser: %i\n", i, pairs[i].winner, pairs[i].loser);

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
bool check_cycle(int target, int start)
{
    if (start == target)
        return true; // cycle detected

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[start][i])
        {
            if (check_cycle(target, i))
                return true;
        }
    }
    return false; // no cycle
}

void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        // Lock only if adding this edge does NOT create a cycle
        if (!check_cycle(pairs[i].winner, pairs[i].loser))
            locked[pairs[i].winner][pairs[i].loser] = true;
    }
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool f = true;
        int j;
        for (j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
                f = false;
        }

        if (f)
            printf("%s\n", candidates[i]);
    }
    return;
}
