#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

// Initialise functions
int count_words(char text[]);
int count_letters(char text[]);
int count_sentences(char text[]);

int main(void)
{
    // Declare variable for text 
    char text[1024];

    // Accept user input
    printf("Text: ");
    fgets(text, sizeof(text), stdin);

    // Remove new line '\n' from string
    text[strcspn(text, "\n")] = '\0';

    // Call functions to assign values to variables
    int words = count_words(text);
    int letters = count_letters(text);
    int sentences = count_sentences(text);

    // Coleman-Liau index to rate reading level
    float index = 0.0588 * (((float) letters / words) * 100.0) - 0.296 * (((float) sentences / words) * 100.0) - 15.8;

    // Grade text according to the Coleman-Liau index
    if (words == 0)
    {
        printf("Invalid Sentence\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", (int) round(index));
    }

    return 0;
}
// Function to calculate and return number of words in the text
int count_words(char text[])
{
    int words = 1;

    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isspace(text[i]))
        {
            words++;
        }
    }
    return words;
}
// Function to calculate and return number of letters in the text
int count_letters(char text[])
{
    int letters = 0;

    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
    }
    return letters;
}
// Function to calculate and return number of sentences in the text
int count_sentences(char text[])
{
    int sentences = 0;

    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }
    return sentences;
}