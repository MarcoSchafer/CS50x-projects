#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

    /*  TO DO:
                Do not count invalid vote as a vote (vote_count)
    */ 

// Define maximum number of canidates
#define MAX 9

// Candidates have name and vote count
typedef struct 
{
    char name[50];
    int votes;
}candidate;

// Declare Array of candidates
candidate candidates[MAX];

// Declare variable for number of candidates
int candidate_count;

// Functions prototypes
bool vote(char *name);
void print_winner(void);

int main(int argc, char *argv[])
{
    // Declare variables
    int voter_count, result;

    if (argc < 2)
    {
        printf("Usage: ./plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 1;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        strcpy(candidates[i].name, argv[i + 1]);
        candidates[i].votes = 0;
    }

    // Prompt user for number of voters
    do {
        printf("Number of voters: ");
        result = scanf("%i", &voter_count);

        if (result != 1)
        {
            printf("Invalid input\n");
            while (getchar() != '\n');      // discard until newline
        }      
    }while (result != 1 || voter_count > MAX);
    
    // Consume leftover newline
    while (getchar() != '\n');

    // Voting loop only counts valid votes
    int valid_votes = 0;
    while (valid_votes < voter_count)
    {
        char name[50];
        printf("Vote: ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = '\0';       // Remove newline from string

        if (!vote(name))
        {
            printf("Invalid vote\n");
        }
        else
        {
            valid_votes++;      // Only increment valid votes 
        }
    }
    
    // Call print_winner function
    print_winner();
    return 0;           
}
// Iterate over candidates, check if name matches candidate name and updates vote count
bool vote(char *name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Function to check who has the most votes and print the winner
void print_winner (void)
{
    int most_votes = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > most_votes)
        {
            most_votes = candidates[i].votes;
        }
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == most_votes)
        {
            printf("Winner: %s\n", candidates[i].name);
        }
    }    
    return;
}