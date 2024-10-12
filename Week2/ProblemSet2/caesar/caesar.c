#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    // check if the number of arguments is incorrect
    if (argc != 2)
    {
        printf("This program requires a single non-negative integer as argument. For example: "
               "./caesar 123\n");
        return 1;
    }

    // check if the argument contains non-digits:
    int current = 0;
    while (argv[1][current] != '\0')
    {
        char c = argv[1][current];
        if ((c < 48) || (c > 57))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }

        current++;
    }

    // parse argument
    int key = atoi(argv[1]);

    // argument value cannot be negative
    if (key < 0)
    {
        return 1;
    }

    // fix the case where the argument is greater than 27:
    key = key % 26;

    // get text to encrypt from the user
    string input = get_string("plaintext:\n");

    // encrypt text
    current = 0;
    while (input[current] != '\0')
    {
        unsigned char c =
            input[current]; // char is unsigned to avoid overflow problems further down
        bool capital = (c >= 65 && c <= 90);
        bool small = (c >= 97 && c <= 122);
        if (capital || small)
        {
            c += key;
            if (((c > 90) && capital) || // capital letters
                ((c > 122) && small))    // small letters
            {
                c = c - 26;
            }

            input[current] = c;
        }

        current++;
    }

    printf("ciphertext: %s\n", input);
}
