#include <stdio.h>

int find_max(int arr[], int size)
{
    int max = arr[0]; // Assume the first element is the maximum
    for (int i = 1; i <= size; i++)
    { // Logic error: should be i < size
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}

int main()
{
    int numbers[] = {1, 3, 5, 7, 9};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    int max = find_max(numbers, size);

    printf("The maximum number is: %d\n", max);
    return 0;
}
