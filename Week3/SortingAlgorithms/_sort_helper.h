extern void print_array(int arr[], int array_length);

extern void swap(int *px, int *py);

extern void print_array(int arr[], int array_length)
{
    printf("[");
    for (int i = 0; i < array_length - 1; i++)
    {
        printf("%i, ", arr[i]);
    }
    printf("%i]\n", arr[array_length - 1]);
}

extern void swap(int *px, int *py)
{
    int bucket = *px;
    *px = *py;
    *py = bucket;
}
