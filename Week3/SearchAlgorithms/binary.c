#include <cs50.h>
#include <stdio.h>

int binary_search(int arr[], int number, int start, int end);

int main(void)
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9}; // sorted array
    int length = sizeof(arr) / sizeof(int);
    int input = get_int("Please enter an integer:\n");
    int result = binary_search(arr, input, 0, length - 1);
    if (result == -1)
    {
        printf("Your number was not found in the array\n");
    }
    else
    {
        printf("Your number was found at index %i\n.", result);
    }
}

int binary_search(int arr[], int number, int start, int end)
{

    while (end - start >= 0)
    {
        int midpoint = start + (end - start) / 2;
        if (arr[midpoint] == number)
        {
            return midpoint;
        }
        else if (number < arr[midpoint]) // search left
        {
            return binary_search(arr, number, start, midpoint - 1);
        }
        else if (number > arr[midpoint]) // search right
        {
            return binary_search(arr, number, midpoint + 1, end);
        }
    }

    return -1;
}
