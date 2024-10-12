#include <cs50.h>
#include <math.h>
#include <stdio.h>

int count_letters(string L);
int count_sentences(string S);
int count_words(string text);

int main(void)
{
    string input = get_string("Text: ");
    int W = count_words(input); // W is the number of words
    double L = count_letters(input) * 100.00 /
               W; // not the average number of letters per 100 words in the text
    double S = count_sentences(input) * 100.00 /
               W; // not the average number of sentences per 100 words in the text

    int index = round(0.0588 * L - 0.296 * S - 15.8);

    // Printing Grade:
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) index);
    }
}

// Additional Functions

int count_letters(string text)
{
    int L = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        char isupper = text[i] >= 'A' && text[i] <= 'Z';
        char islower = text[i] >= 'a' && text[i] <= 'z';
        if (isupper || islower)
        {
            L++;
        }
    }
    return L;
}

int count_sentences(string text)
{
    int S = 0;
    for (int i = 0; text[i]; i++)
    {
        char isdot = text[i] == '.' ? 1 : 0;
        char isquestion = text[i] == '?' ? 1 : 0;
        char isexclaimation = text[i] == '!' ? 1 : 0;
        if (isdot || isquestion || isexclaimation)
        {
            S++;
        }
    }
    return S;
}

int count_words(string text)
{
    int W = 1;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == ' ')
        {
            W++;
        }
    }

    if (text[0] == '\0')
    {
        W = 0;
    }
    return W;
}
