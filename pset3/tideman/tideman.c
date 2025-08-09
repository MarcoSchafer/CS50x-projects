#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Define maximum number of candidates
#define MAX 9

// preference[i][j] is the number of voters that prefer i over j 
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner and loser
typedef struct 
{
    int winner;
    int loser;
}pair;

// Array of candidates
char *candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

// Create global variables
int result, pair_count, voter_count, candidate_count;

// Function prototypes
bool vote(int rank, char *name, int ranks[]);
void record_preference(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool cycle(int winner, int loser);

int main(int argc, char *argv[])
{
    // Check for valid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)        // check if number of candidates is within range
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 1;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear locked pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    // Prompt for number of voters (only accept ints)
    do
    {
        printf("Number of voters: ");
        result = scanf("%i", &voter_count);

        if (result != 1)
        {
            printf("Invalid input\n");
            while (getchar() != '\n');      // discard until newline
        }
    } while (result != 1);

    while (getchar() != '\n');                          // consume leftover newline
    pair_count = 0;                                     // set pair count to 0
    memset (preferences, 0, sizeof(preferences));       // Reset preferences

    // Prompt for votes (only accept valid votes)
    for (int i = 0; i < voter_count; i++)
    {
        int ranks[candidate_count];

        for (int j = 0; j < candidate_count; j++)
        {
            while(true)
            {
                char name[50];
                printf("Rank %i: ", j + 1);
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';       // remove newline from string

                if (vote(j, name, ranks))
                {
                    break;
                }
                else
                {
                    printf("Invalid vote\n");
                }
            }
        }
        record_preference(ranks);
        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks 
bool vote(int rank, char *name, int ranks[])
{
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

// Update preferences
void record_preference(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
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
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            } 
        }
    }
    return;
}

// Sort pairs in descending order by margin of victory
void sort_pairs(void)
{
    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = 0; j < pair_count - i - 1; j++)
        {
            int margin1 = preferences[pairs[j].winner][pairs[j].loser];
            int margin2 = preferences[pairs[j + 1].winner][pairs[j + 1].loser];
            if (margin1 < margin2)
            {
                pair temp = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temp;
            }
        }
    }
    return;
}

// Lock pairs in order without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!cycle(pairs[i].winner, pairs[i].loser))
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
        bool winner = true;

        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                winner = false;
                break;
            }
        }
        
        if (winner == true)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}

// 
bool cycle(int winner, int loser)
{
    if (loser == winner)
    {
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i] == true)
        {
            if (cycle(winner, i) == true)
            {
                return true;
            }
        }
    }
    return false;
}