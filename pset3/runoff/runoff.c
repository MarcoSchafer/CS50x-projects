#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Define max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// 
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Struct for candidate's name, vote count, eliminated status
typedef struct
{
    char name[50];
    int votes;
    bool eliminated;
}candidate;

// Array of candidates
candidate candidates [MAX_CANDIDATES];

// Global variables declaration
int voter_count, candidate_count, result;

// Function prototypes
bool vote(int voter, int rank, char *name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminated(int min);

int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: Runoff [candidate...]\n");
        return 1;
    }
    
    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 1;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        strcpy(candidates[i].name, argv[i + 1]);
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    // Prompt for number of voters (accept only ints)
    do
    {
        printf("Number of voters: ");
        result = scanf("%i", &voter_count);

        if (result != 1)
        {
            printf("Invalid input\n");
            while (getchar() != '\n');      // discard until newline
        }
    } while (result != 1 || voter_count > MAX_VOTERS);

    while (getchar() != '\n');      // consume leftover newline
    
    // Prompt user for votes (only accept valid votes)
    int valid_votes = 0;
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            char name[50];
            printf("Rank %i: ", j + 1);
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = '\0';       // remove newline from string

            if (!vote(i, j, name))
            {
                printf("Invalid vote\n");
            }
            else
            {
                valid_votes++;      // only increment valid votes
            }
        }
        printf("\n");       // print newline
    }

    // Keep holding runoffs until winner exists
    while (/*condition*/)
    {
        /* code */
    }
    
    

    return 0;
}
// Record preference if vote is valid
bool vote(int voter, int rank, char *name)
{

}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{

}

// Print winner of election if applicable
bool print_winner(void)
{

}

// Return minimum number of votes remaining candidates have
int find_min(void)
{

}

// Return true if election is tied between all candidates
bool is_tie(int min)
{

}

// Eliminate candidate in last place
void eliminated(int min)
{

}