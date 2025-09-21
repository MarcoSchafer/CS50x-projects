#include <stdio.h>
#include <math.h>

int main(void)
{
    int change = 0;
    int coins = 0;
    
    // Prompt user for change
    do
    {
        printf("Change owed: ");
        scanf("%i", &change);
    } while (change < 0);
    
    int coin_values[] = {25, 10, 5, 1};

    for (int i = 0; i < 4; i++)
    {
        switch (coin_values[i])
        {
            case 25:
                while (change >= 25)
                {
                    change -= 25;
                    coins++;
                }
                break;

            case 10:
                while (change >= 10)
                {
                    change -= 10;
                    coins++;
                }
                break;

            case 5:
                while (change >= 5)
                {
                    change -= 5;
                    coins++;
                }
                break;

            case 1:
                while (change >= 1)
                {
                    change -= 1;
                    coins++;
                }
                break;
        }
    }

    printf("%i\n", coins); // Print number of coins 

}