#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string s = get_string("s: ");
    string t = get_string("t: ");

    printf("Comparing strings using \"==\"\n");
    // this will always return false, since
    // it compares the addresses of the two strings
    if (s == t)
    {
        printf("same\n");
    }
    else
    {
        printf("different\n");
    }

    printf("Comparing strings using strcmp:\n");
    // this works as expected
    if (strcmp(s, t) == 0)
    {
        printf("same\n");
    }
    else
    {
        printf("different\n");
    }
}
