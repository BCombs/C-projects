#include <cs50.h>
#include <stdio.h>
#include <math.h>

void validate(int cardDigits[], int length);

int main(void)
{
    // Holds the length of the card number entered
    int length;
    
    printf("Number: ");
    long long number = get_long_long();
    
    
    // Set the value of length to the length of the number, if it is valid
    if(number <= 0)
    {
        length = 0;
    }
    else
    {
        length = log10(number) + 1;
    }
    
    //Create an array to store each digit of the card number in
    int cardDigits[length];
    
    // Check if the number meets the length requirements, if it does, validate it
    if(length == 13 || length == 15 || length == 16) 
    {
        
        for(int i = length - 1; i >= 0; i--)
        {
            if(number < 10)
            {
                cardDigits[i] = number;
            }
            else
            {
                cardDigits[i] = number % 10;
                number = number / 10;
            }
        }
        
        // Check validity of card number
        validate(cardDigits, length);
    }
    else
    {
        printf("INVALID\n");
    }
}

void validate(int cardDigits[], int length)
{
    //TODO Validate card number
    int phaseOne = 0;
    int phaseTwo = 0;
    
    // Phase One
    // Multiply every other digit by 2, add the digits together
    for(int i = length - 2; i >= 0; i -= 2)
    {
        int currentNumber = cardDigits[i] * 2;
        
        if(currentNumber >= 10)
        {
            phaseOne += currentNumber % 10;
            currentNumber = currentNumber / 10;
            phaseOne += currentNumber;
        }
        else
        {
            phaseOne += currentNumber;
        }
    }
    
    // Phase Two
    // Add phaseOne with every digit that wasn't multiplied by 2
    phaseTwo = phaseOne;
    
    for(int i = length - 1; i >= 0; i -= 2)
    {
        phaseTwo += cardDigits[i];
    }
    
    // Phase 3
    // Check if the card was a valid number, if it is, print which company the number belongs to
    if(phaseTwo % 10 == 0)
    {
        // Check for AMEX
        if(cardDigits[0] == 3 & cardDigits[1] == 4 || cardDigits[1] == 7)
        {
            printf("AMEX\n");
        }
        
        // Check for VISA
        else if(cardDigits[0] == 4)
        {
            printf("VISA\n");
        }
        
        // Check for MASTERCARD
        else if(cardDigits[0] == 5 & cardDigits[1] >= 1 || cardDigits[1] <= 5)
        {
            printf("MASTERCARD\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
