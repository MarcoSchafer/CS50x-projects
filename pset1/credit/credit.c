#include <stdio.h>
#include <stdbool.h>

bool valid(long long num);
int num_digits(long long num);
int start_with(long long num);

int main(void)
{
    // Declare variable for Credit Card Number
    long long num;

    // Prompt for Credit Card Number 
    printf("Credit Card Number: ");     
    if (scanf("%lld", &num) != 1)
    {
        printf("Invalid input\n");
        return 1;
    }

    // Print matching Credit Card
    if (valid(num) && num_digits(num) == 15 && (start_with(num) == 34 || start_with(num) == 37))
    {
        printf("AMEX\n");
    }
    else if (valid(num) && num_digits(num) == 16 && (start_with(num) >= 51 && start_with(num) <= 55))
    {
        printf("MASTERCARD\n");
    }
    else if (valid(num) && (num_digits(num) == 13 || num_digits(num) == 16) && start_with(num) / 10 == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }

    return 0;
}
bool valid(long long num)       // check if card number is valid
{
    // Declare variables
    long long not_mutliplied = num;
    bool second_digit = false;
    int sum = 0;

    // Iterate over num, multiply by 2, and add digit of product to sum
    while (num > 0)
    {
        int digit = num % 10;
        if (second_digit)
        {
            int multiplied = digit * 2;

            if (multiplied > 9)
            {
                sum += multiplied % 10;
                sum += 1;
            }
            else
            {
                sum += multiplied;
            }
        }
        num /= 10;
        second_digit = !second_digit;
    }

    // Add sum to every other digit (not multiplied by 2) starting from the end
    second_digit = true;
    
    while (not_mutliplied > 0)
    {
        if (second_digit)
        {
            sum += not_mutliplied % 10;
        }
        second_digit = !second_digit;
        not_mutliplied /= 10;
    }
    return sum % 10 == 0;
}
int num_digits(long long num)       // calculate number of digits in card num
{
    int count = 0;

    while (num > 0)
    {
        num /= 10;
        count++;
    }
    return count;
}
int start_with(long long num)       // calculate the starting two digits of the card num
{
    while (num >= 100)   // reduce to first two digits
    {
        num /= 10;
    }
    return num;   // returns 2-digit prefix (e.g., 34, 37, 51, 55, 40)
}