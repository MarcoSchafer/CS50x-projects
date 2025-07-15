#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Initialise the calc_scores function
int calc_score(char word[]);

int main(void)
{
    // Declare array for the scores of both players
    int score[2];

    for (int i = 0; i < 2; i++)
    {
        // Declare string of 16 characters because the longest word in Scrabble is 15 characters long and one extra for the null terminator '\0'
        char word[16];

        // Get user input for both players
        printf("Player %i: ", i + 1);
        if (scanf("%15s", word) != 1)
        {
            printf("Error reading input.\n");
            return 1;
        }

        // Flush the rest of the line
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        
        // Assign scores to each player
        score[i] = calc_score(word);
    }

    // Check scores and announce a winner
    if (score[0] > score[1])
    {
        printf("Player 1 Wins!\n");
    }
    else if (score[0] < score[1])
    {
        printf("Player 2 Wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }

}
// calc_scores function to calculate and return the score of a word
int calc_score(char word[])
{
    // Point table for letters of the alphabet
    int points_table[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

    int score = 0;

    // Itterate over the word letter by letter and add to score
    for (int i = 0, len = strlen(word); i < len; i++)
    {
        if (islower(word[i]))
        {
            score += points_table[word[i] - 'a'];
        }
        else if (isupper(word[i]))
        {
            score += points_table[word[i] - 'A'];
        }
    }
    return score;
}