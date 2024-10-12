#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    string key;
    // ok, so this one is a bit excessive, but I'm not very bright and keep getting it wrong so here
    // is a constant to use
    const signed char ALPHABET_LENGTH = 26;

    // check if number of arguments is 1 and if not print error message and return 1
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    key = argv[1];

    // verify key is letter
    unsigned char c = key[0];
    int keyLength = 0;
    while (c != '\0')
    {
        if (((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) == false)
        // c is not a letter
        {
            printf("Key must contain only letters\n");
            return 1;
        }

        keyLength++;
        c = key[keyLength];
    }

    // check key length
    if (keyLength != ALPHABET_LENGTH)
    {
        printf("The key must contain %u unique characters\n", ALPHABET_LENGTH);
        return 1;
    }

    // set all letters in the key to lowercase
    for (int i = 0; i < ALPHABET_LENGTH; i++)
    {
        key[i] = key[i] | 0x20;
    }

    // check for duplicate letters in the key
    for (int i = 0; i < ALPHABET_LENGTH; i++)
    {
        char keyi = key[i];

        for (int k = i + 1; k < ALPHABET_LENGTH; k++)
        // compare all characters to the right of key[i] with itself
        {
            char keyk = key[k];

            if (keyi == keyk)
            {
                printf("The key must contain %u unique characters\n", ALPHABET_LENGTH);
                return 1;
            }
        }
    }

    // read input from the user
    string text = get_string("plaintext:  ");

    // encrypt each character
    c = text[0];
    int current = 0;
    while (c != '\0')
    {
        if ((c >= 65 && c <= 90)) // c is capital
        {
            int index = c - 65;
            text[current] = key[index] & ~0x20; // set to uppercase (set 6th bit to 1)
        }
        else if (c >= 97 && c <= 122) // c is lowercase
        {
            int index = c - 97;
            text[current] = key[index];
        }

        current++;
        c = text[current];
    }

    // print the result
    printf("ciphertext: %s\n", text);
}
