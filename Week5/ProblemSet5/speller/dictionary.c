// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Choose number of buckets in hash table
// these stats are when the lists in the hash table append new elements at the end
// I fixed the list to append at position 0 since then, but am leaving these values for reference
// const unsigned int N = 233;      // .15 secs
// const unsigned int N = 997;      // .12 secs
const unsigned int N = 10133; //    // 0.08
                              // anything more than this seems like a waste of memory
// const unsigned int N = 71777;    // 0.09 secs
// const unsigned int N = 143091;   // 0.08 secs // same number as words in the dictionary. Not
//                                                  perfect table tho.
// const unsigned int N = 250007;   // 0.10 secs // this is more than the words in the dictionary

// I've been told using prime numbers results in better distribution
// so I want to test that:
// const unsigned int N = 262144;   // (=2^18) 0.61 -> way slower than 250007
// const unsigned int N = 8192;     // (=2^13) 1.68 -> way slower than 10133 (0.08)
// const unsigned int N = 16384;    // (=2^14) 1.63 -> way slower than 10133 (0.08)
// const unsigned int N = 10000;    // 0.11 -> slightly slower than 10133
// const unsigned int N = 1;        // 4.47 this is a list basically-> waaay slower

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    if (word == NULL)
    {
        return false;
    }

    // lowercase word
    char word_lowercase[LENGTH + 1];
    int index = 0;
    while (word[index] != '\0')
    {
        word_lowercase[index] = tolower(word[index]);
        index++;
    }
    word_lowercase[index] = '\0';

    // search word
    node *ptr = table[hash(word)]; // the hash table is case insensitive
    while (ptr != NULL)
    {
        int i = 0;
        while (ptr->word[i] != '\0')
        // this while loop compares two strings up until \0.
        // when I tried using strcmp() valgrind would warn me of accessing
        // uninitialized characters (the ones after \0 in the array maybe?)
        // and I couldnt make it work without warnings, so I made this instead
        // TODO: implement fscanf() when loading and strcmp() here
        {
            if (ptr->word[i] != word_lowercase[i])
            {
                break;
            }

            i++;
        }

        if (ptr->word[i] == '\0' && word_lowercase[i] == '\0')
        {
            return true;
        }

        ptr = ptr->next;
    }
    return false;
}

// Hashes word to a number
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

        // I find this part less readable and slower if
        // implemented with a loop, so I'm leaving it as is
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

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // initialize hash table to avoid garbage values
    for (int n = 0; n < N; n++)
    {
        table[n] = NULL;
    }

    // open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // read char by char
    char new_word[LENGTH + 1];
    int index = 0;
    char *buffer = malloc(sizeof(char));
    if (buffer == NULL)
    {
        printf("Out of memory\n");
        return false;
    }
    int debuginfoindex = 0;
    // use fscanf() here and strcpy()
    while (fread(buffer, sizeof(char), 1, file))
    {
        if (*buffer != '\n') // word not ended, keep loading characters
        {
            new_word[index++] = *buffer;
        }
        else // end of word, insert it in hash table
        {
            // terminate the string
            new_word[index] = '\0';

            // load word in a new node for the hash table
            node *new_node = malloc(sizeof(node));
            if (new_node == NULL)
            {
                printf("Out of memory\n");
                return false;
            }
            new_node->next = NULL;
            for (int i = 0; i < index; i++)
            {
                new_node->word[i] = new_word[i];
            }
            new_node->word[index] = '\0';
            index = 0;

            // append new node to hash table
            unsigned int hash_value = hash(new_word);
            if (table[hash_value] == NULL)
            {
                table[hash_value] = new_node;
            }
            else
            {
                new_node->next = table[hash_value];
                table[hash_value] = new_node;
            }
        }
    }
    // // THIS PART PRINTS DISTRIBUTION OF HASH TABLE
    // printf("\n");
    // printf("Buckets: %i\n", N);
    // for (int i = 0; i < N; i++)
    // {
    //     printf(" Words in next bucket %i:\n", i + 1);
    //     node *ptr = table[i];
    //     int wordcount = 0;
    //     printf("  ");
    //     while (ptr != NULL)
    //     {
    //         wordcount++;
    //         printf("%s, ", ptr->word);
    //         ptr = ptr->next;
    //     }
    //     printf("\n");
    //     printf("bucket %3i/%i: %i words\n", i + 1, N, wordcount);
    // }

    free(buffer);
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    unsigned int count = 0;
    for (int i = 0; i < N; i++)
    {
        node *ptr = table[i];
        while (ptr != NULL)
        {
            count++;
            ptr = ptr->next;
        }
    }
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *ptr_next = NULL;
    node *ptr = NULL;
    for (int i = 0; i < N; i++)
    {
        ptr = table[i];
        while (ptr != NULL)
        {
            ptr_next = ptr->next;
            if (ptr != NULL)
            {
                free(ptr);
            }
            ptr = ptr_next;
        }
    }
    return true;
}
