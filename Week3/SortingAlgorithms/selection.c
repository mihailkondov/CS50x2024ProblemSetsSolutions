#include <stdio.h>
#include "_sort_helper.h"

void selection_sort(int arr[], int array_length);

int main(void)
{
    int arr[] = {9, 1, 3, 5, 8, 2, 4, 7, 6};
    int array_length = sizeof(arr) / sizeof(int);
    print_array(arr, array_length);
    selection_sort(arr, array_length);
    print_array(arr, array_length);
}

void selection_sort(int arr[], int array_length)
{
    for (int i = 0; i < array_length - 1; i++)
    {
        int min = arr[i];
        for (int j = i + 1; j < array_length; j++)
        {
            if (arr[j] < min)
            {
                min = arr[j];
                swap(&arr[i], &arr[j]);
            }
        }
    }
}
