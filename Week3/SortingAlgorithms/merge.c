#include <stdio.h>
#include "_sort_helper.h"

void merge_sort(int arr[], int array_length);

int main(void)
{
    int arr[] = {9, 1, 3, 5, 8, 2, 4, 7, 6};
    // int arr[] = {9, 8, 7, 6, 5, 1, 4, 3, 2};
    int array_length = sizeof(arr) / sizeof(int);
    print_array(arr, array_length);
    merge_sort(arr, array_length);
    print_array(arr, array_length);
}

void merge_sort(int arr[], int array_length)
{
    int odd = array_length % 2;
    int half_length = array_length / 2;
    int left[half_length];
    int right[half_length + odd];
    int right_index = half_length;
    for (int i = 0; i < half_length; i++, right_index++) // split the arrays
    {
        left[i] = arr[i];
        right[i] = arr[right_index];
    }

    if (odd == 1)
    {
        right[half_length] = arr[array_length - 1];
    }

    // recursive call on the two halves
    if (half_length > 1)
    {
        merge_sort(left, half_length);
    }

    if (half_length + odd > 1)
    {
        merge_sort(right, half_length + odd);
    }

    // base case
    printf("merging:\n");
    print_array(left, half_length);
    print_array(right, half_length + odd);

    for (int i = 0; i < half_length + odd; i++)
    {
        arr[i] = left[i];
    }

    for (int i = half_length + odd; i < array_length; i++)
    {
        arr[i] = right[i - half_length - odd];
    }

    int cursor_left = 0;
    int cursor_right = 0;
    for (int i = 0; i < array_length; i++)
    {
        if (right[cursor_right] < left[cursor_left])
        {
            if (cursor_right < half_length + odd)
            {
                arr[i] = right[cursor_right];
                cursor_right++;
            }
            else // right is depleted, take from left
            {
                arr[i] = left[cursor_left];
                cursor_left++;
            }
        }
        else // left is smaller
        {
            if (cursor_left < half_length) // insert left
            {
                arr[i] = left[cursor_left];
                cursor_left++;
            }
            else // left is depleted, so take from right
            {
                arr[i] = right[cursor_right];
                cursor_right++;
            }
        }
    }

    printf("merged: ");
    print_array(arr, array_length);
}
