#include <stdio.h>

int main (void)
{
    //Declare variables
    int height;

    //Prompt user for input
    do
    {
        printf("Height: ");
        scanf("%i", &height);
    } while (height < 1 || height > 8);
    
    //Print rows
    for (int i = 0; i < height; i++)
    {
        //Print spaces
        for (int s = 0; s < height - i - 1;s++)
        {
            printf(" ");
        }

        //Print blocks
        for (int b = 0; b <= i; b++)
        {
            printf("#");
        }

        //Print column gap
        printf("  ");

        //Print second traingle
        for (int j = height + i + 1; j > height; j--)
        {
            printf("#");
        }
        
        //Print new line
        printf("\n");
    }

}