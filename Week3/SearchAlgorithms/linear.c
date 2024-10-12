#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int arr[] = {3, 6, 1, 5, 4, 9};
    int length = sizeof(arr) / sizeof(int);
    int input = get_int("Please enter a number:\n");

    printf("Searching for %i:\n", input);

    for (int i = 0; i < length; i++)
    {
        if (arr[i] == input)
        {
            printf("Number found at index %i in the array.\n", i);
            return 0;
        }
    }

    printf("The number you entered is not in the array.\n");
    return 0;
}
