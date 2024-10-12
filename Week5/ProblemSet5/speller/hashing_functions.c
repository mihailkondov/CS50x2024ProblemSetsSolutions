/*
This code is not supposed to compile as is, I just paste the old hashing
functions from speller for later reference some versions of hashing functions
*/

// Default
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Version 1
unsigned int hash(const char *word)
{

    unsigned int result = 0;
    unsigned char c = word[0];
    for (int i = 0; c != '\0'; i++, c = word[i])
    {
        result += tolower(c) * i;
    }
    return result % N;
}

// initial implementation of this
// https://youtu.be/DMQ_HcNSOAI?t=443

unsigned int hash(const char *word)
{
    unsigned char c = word[0];
    int i = 0;
    while (word[i] != '\0')
    {
        i++;
    }

    if (i > 1)
    {
        char c0 = toupper(word[0]);
        char c1 = toupper(word[1]);
        char c8 = toupper(word[i]);
        char c9 = toupper(word[i - 1]);

        unsigned int bytes4 = 0;
        memcpy(&bytes4, &c0, 1);
        bytes4 = bytes4 << 8;
        memcpy(&bytes4, &c1, 1);
        bytes4 = bytes4 << 8;
        memcpy(&bytes4, &c8, 1);
        bytes4 = bytes4 << 8;
        memcpy(&bytes4, &c9, 1);
        return bytes4 % N;
    }
    else
    {
        return (toupper(word[0]) - 'A') % N;
    }
}

// rewrote the same hashing function as above, but with a loop
unsigned int hash(const char *word)
{
    unsigned char c = word[0];
    int i = 0;
    while (word[i] != '\0')
    {
        i++;
    }

    if (i > 1)
    {
        char arr[4];
        arr[0] = toupper(word[0]);
        arr[1] = toupper(word[1]);
        arr[2] = toupper(word[i]);
        arr[3] = toupper(word[i - 1]);

        unsigned int bytes4 = 0;
        memcpy(&bytes4, &arr[0], 1);
        for (int j = 1; j < 4; j++)
        {
            bytes4 = bytes4 << 8;
            memcpy(&bytes4, &arr[j], 1);
        }

        return bytes4 % N;
    }
    else
    {
        return (toupper(word[0]) - 'A') % N;
    }
}

// // THIS PART PRINTS DISTRIBUTION OF HASH TABLE
// printf("Buckets: %i\n", N);
// for (int i = 0; i < N; i++)
// {
//     node *ptr = table[i];
//     int wordcount = 0;
//     while (ptr != NULL)
//     {
//         wordcount++;
//         ptr = ptr->next;
//     }
//     printf("  bucket %3i/%i: %i words\n", i + 1, N, wordcount);
// }
// ///
