#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // prompt the user to give a valid size which is also not too big:
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height > 8 || height < 1);

    // print the pyramid:
    for (int i = 0; i < height; i++)
    {
        for (int k = height - i - 1; k > 0; k--)
        {
            printf(" ");
        }
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}

