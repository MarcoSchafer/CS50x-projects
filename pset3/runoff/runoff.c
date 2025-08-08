#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <ctype.h>

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
void eliminate(int min);
void normalise(char *str);

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
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            while(true)
            {
                char name[50];
                printf("Rank %i: ", j + 1);
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';       // remove newline from string           
            
                if (vote(i, j, name))
                {
                    break;
                }
                else
                {
                    printf("Invalid vote\n");      // only increment on valid votes
                }
            }
        }
        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        tabulate();

        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate candidates in last place
        int min = find_min();
        bool tie = is_tie(min);

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

        // Elimiate candidates with votes = min
        eliminate(min);

        // Reset vote count
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Trim spaces and lowercase
void normalise(char *str)
{
    while (*str == ' ') str++;      // trim leading spaces

    // Trim trailing spaces
    char *end = str + strlen(str) - 1;
    while (end >= str && *end == ' ') end--;
    *(end + 1) = '\0';

    // Convert to lower case
    for (char *p = str; *p; p++)
    {
        *p = tolower(*p);
    }
}

// Record preference if vote is valid
bool vote(int voter, int rank, char *name)
{
    normalise(name);

    char temp[50];
    for (int i = 0; i < candidate_count; i++)
    {
        strcpy(temp, candidates[i].name);
        normalise(temp);

        if (strcmp(name, temp) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {   
            if (!candidates[preferences[i][j]].eliminated)
            {
                candidates[preferences[i][j]].votes++;
                break;
            }
        }
    }
    return;
}

// Print winner of election if applicable
bool print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > voter_count / 2)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return minimum number of votes remaining candidates have
int find_min(void)
{
    int least_votes = INT_MAX;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes < least_votes && !candidates[i].eliminated)
        {
            least_votes = candidates[i].votes;
        }
    }
    return least_votes;
}

// Return true if election is tied between all candidates
bool is_tie(int min)
{
    int count = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes != min && !candidates[i].eliminated)
        {
            return false;
        }
    }
    return true;
}

// Eliminate candidate/s in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {  
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}