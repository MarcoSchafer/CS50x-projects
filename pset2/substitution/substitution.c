#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // Check if correct number of command line arguments 
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Check if command line argument argv[1] contains 26 characters
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters\n");
        return 1;
    }

    // iterate over key and check if all characters are alphabetic and not repetitive
    int seen[26] = {0};
    for (int i = 0; i < 26; i++)
    {
        char c = toupper(argv[1][i]);
        if (!isalpha(c))
        {
            printf("Key must contain alphabetic characters\n");
            return 1;
        }
        int index = c - 'A';
        if (seen[index])
        {
            printf("Key cannot contain repeated characters\n");
            return 1;
        }
        seen[index] = 1;
    }

    // Prompt user for plaintext input
    char input[512];
    printf("Plaintext: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';     // Remove newline

    int len = strlen(input);    // Create string lenght variable to re-use
    char ciphertext[512];       // Array of chars (string) for ciphertext

    // Iterate over plaintext and apply encryption
    for (int i = 0; i < len; i++)
    {
        if (isupper(input[i]))
        {
            ciphertext[i] = toupper(argv[1][input[i] - 'A']);
        }
        else if (islower(input[i]))
        {
            ciphertext[i] = tolower(argv[1][input[i] - 'a']);
        }
        else
        {
            ciphertext[i] = input[i];
        }
    }

    // Add null terminator to end of string 
    ciphertext[len] = '\0';

    // Print encrypted text
    printf("Ciphertext: %s\n", ciphertext);
}