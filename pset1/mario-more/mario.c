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
    
    printf("%i", height);
}