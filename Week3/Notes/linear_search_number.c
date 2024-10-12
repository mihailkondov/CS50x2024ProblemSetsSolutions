#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int numbers[] = {10, 100, 50, 80};

    int n = get_int("Number: \n");
    for (int i = 0; i < 4; i++)
    {
        if (numbers[i] == n)
        {
            printf("Found\n");
            return 0;
        }
    }
    printf("Not found\n");
    return 1;
}
