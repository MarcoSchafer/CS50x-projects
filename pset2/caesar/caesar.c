#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

bool only_digits(char *str);

int main(int argc, char *argv[])
{
    // Check if correct input has been provided
    if (argc != 2 || !only_digits(argv[1]))
    {
        printf("Invalid Input. Usage: ./caesar key\n");
        return 1;
    }

    // Convert char to int
    int key = atoi(argv[1]);

    // Create a char array and promt for plaintext
    char input [256];
    printf("Plaintext: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';     // Remove new-line

    printf("Ciphertext: ");

    // Iterate over plaintext and apply encryption  
    for (int i = 0; input[i] != '\0'; i++)
    {
        if (isupper(input[i]))
        {
            printf("%c", (input[i] - 65 + key) % 26 + 65);
        }
        else if (islower(input[i]))
        {
            printf("%c", (input[i] - 97 + key) % 26 + 97);
        }
        else
        {
            printf("%c", input[i]);
        }
    }

    return 0;
}
// Function to check if string contains only digits
bool only_digits(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!isdigit((unsigned char)str[i]))
        return false;
    }

    return true;
}