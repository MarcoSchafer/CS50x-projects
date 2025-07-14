#include <stdio.h>

int main (void)
{
    //Declare variables
    int height;

    //Get user input for height of pyramid
    do
    {
        printf("Height: ");
        scanf("%i", &height);
    } while (height < 1 || height > 8);

    //Print rows    
    for (int i = 0; i < height; i++)
    {
        //Print spaces
        for (int s = 0; s < height - i - 1; s++)
        {
            printf(" ");
        }
        //Print blocks
        for (int b = 0; b <= i; b++)
        {
            printf("#");
        }
        //Print New line
        printf("\n");
    }

}