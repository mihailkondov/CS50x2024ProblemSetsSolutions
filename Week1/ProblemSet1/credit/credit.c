#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

bool is_luhn_valid(long cardnumber);

int main(void)
{
    int luhnCheck = 0;
    int sum1 = 0;
    int sum2 = 0;
    long input;
    string type = "INVALID";

    input = get_long("Enter card number:\n");
    printf("number entered: %lu\n", input);

    if (is_luhn_valid(input) == false) // Check sums
    {
        printf("INVALID\n");
        return 0;
    }

    if ((input >= 4000000000000 && input <= 4999999999999) ||
        (input >= 4000000000000000 && input <= 4999999999999999)) // VISA
    {
        type = "VISA";
    }
    else if ((input >= 340000000000000 && input <= 349999999999999) ||
             (input >= 370000000000000 && input <= 379999999999999)) // AMEX
    {
        type = "AMEX";
    }
    else if (input >= 5100000000000000 && input <= 5599999999999999) // MASTERCARD
    {
        type = "MASTERCARD";
    }

    printf("%s\n", type);
    return 0;
}

bool is_luhn_valid(long cardnumber)
{
    int firstsSum = 0;
    int secondsSum = 0;
    long current;

    // determine first sum:
    current = cardnumber;
    while (current > 0)
    {
        firstsSum += current % 10; // take last digit
        current /= 100;            // remove last two digits
    }

    // determine second sum:
    current = cardnumber;
    while (current > 0)
    {
        current /= 10;                 // delete last digit
        int digitValue = current % 10; // take second to last digit
        digitValue *= 2;               // double it
        int digit1 = digitValue / 10;  // take product's first digit
        int digit2 = digitValue % 10;  // take product's second digit
        secondsSum += digit1 + digit2; // add the two product's digits to the sum
        current /= 10;                 // delete second to last digit
    }

    if ((firstsSum + secondsSum) % 10 == 0)
    {
        return true;
    }

    return false;
}
