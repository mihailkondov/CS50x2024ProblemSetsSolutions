#include <stdio.h>
#include "_sort_helper.h"

void insertion_sort(int arr[], int array_length);

int main(void)
{
    int arr[] = {5, 3, 1, 2, 9, 8, 6, 7, 4};
    int array_length = sizeof(arr) / sizeof(int);
    print_array(arr, array_length);
    insertion_sort(arr, array_length);

}

void insertion_sort(int arr[], int array_length)
{
    for (int i = 1; i < array_length; i++)
    {
        int j = i - 1;
        while(arr[j + 1] < arr[j] && j >= 0)
        {
            swap(&arr[j + 1], &arr[j]);
            j--;
            print_array(arr, array_length);
        }
    }
}
