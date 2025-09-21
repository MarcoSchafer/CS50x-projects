# Problem Set 1 : Credit

This project is a C program that validates credit card numbers using **Luhn’s Algorithm** and identifies the type of card.  
The program checks if the number corresponds to **AMEX**, **MasterCard**, or **VISA**, or reports it as **INVALID**.

## How It Works

1. Prompts the user for a credit card number.
2. Runs Luhn’s Algorithm to verify the checksum.
3. Checks the length and starting digits to determine the card type:
   - **AMEX** → 15 digits, starts with 34 or 37
   - **MasterCard** → 16 digits, starts with 51–55
   - **VISA** → 13 or 16 digits, starts with 4
4. Prints the card type or `INVALID` if the number does not match any valid pattern.

## How to Compile

Use GCC to compile the program:

```bash
gcc -o credit credit.c
```

How to Run:
```bash
./credit
```