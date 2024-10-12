#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string words[] = {"alpha", "beta", "gamma", "delta"};
    int n = 4;
    string input = get_string("Enter word you are searching for:\n");
    for (int i = 0; i < n-1; i++)
    {
        if (!strcmp(words[i], input))
        {
            printf("Found\n");
            return 0;
        }
    }
    printf("Not found\n");
    return 1;

}