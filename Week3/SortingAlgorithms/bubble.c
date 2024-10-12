#include <stdio.h>
#include "_sort_helper.h"

void bubbleSort(int arr[], int length);

void printArray(int arr[], int length);

int main()
{
    int arr[] = {64, 25, 12, 22, 11};
    int n = sizeof(arr) / sizeof(arr[0]);
    bubbleSort(arr, n);
    printf("Sorted array: \n");
    printArray(arr, n);
    return 0;
}

void bubbleSort(int arr[], int length)
{
    for (int i = 0; i < length; i++)
    {
        for (int j = i + 1; j < length; j++)
        {
            if (arr[i] > arr[j])
            {
                swap(&arr[i], &arr[j]);
            }
        }
    }
}

void printArray(int arr[], int length)
{
    printf("[");
    for (int i = 0; i < length - 1; i++)
    {
        printf("%i, ", arr[i]);
    }
    printf("%i]\n", arr[length - 1]);
}

