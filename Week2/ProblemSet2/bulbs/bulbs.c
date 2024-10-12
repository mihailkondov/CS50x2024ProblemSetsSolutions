#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    string input = get_string("Enter input: \n");
    int symbols = strlen(input);
    for (int i = 0; i < symbols; i++)
    {
        char c = input[i];
        int bits[BITS_IN_BYTE];
        int k = 128;

        for (int j = 1; j <= 8; j++)
        {
            bits[j] = c / k;
            if (bits[j] > 0)
            {
                c = c - k;
            }
            k = k / 2;
            print_bulb(bits[j]);
        }
        printf("\n");
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}