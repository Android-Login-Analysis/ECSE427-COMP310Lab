#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#define SIZE 30

void swap(int arr[], int left, int right);
int partition(int arr[], int lowIndex, int highIndex, int pivot);

struct argument
{
    int lowIndex;
    int *arr;
    int highIndex;
};

void *quicksort(void *args)
{

    // create two pointers vars to structure because we will launch quicksort on one half in a new thread.
    // we will let this thread continue its execution for quicksort of other half -- to avoid wasting this thread, we
    // will not spawn a new thread for the other half.

    // assign the input pointer to helper_1 only, we will assign values to helper_2 based using helper_1 itself.
    struct argument *helper_1 = args;
    struct argument helper_2;

    int lowIndex = helper_1->lowIndex;
    int highIndex = helper_1->highIndex;
    int *arr = helper_1->arr;

    pthread_t thread_2;

    if (lowIndex >= highIndex)
    {
        return NULL;
    }

    // randomly assign the pivot
    // int pivotIndex = lowIndex + rand() % (highIndex + 1 - lowIndex);
    // int pivot = arr[pivotIndex];
    int pivot = arr[highIndex];

    // swap(arr, pivotIndex, highIndex);
    int left = partition(arr, lowIndex, highIndex, pivot);

    // helper_1->lowIndex = lowIndex; To show that we want helper_1 to have its original lowIndex value
    // we are readying helper_1 as argument for quicksort call from lowIndex to left-1 on arr.
    helper_1->highIndex = left - 1;
    // helper_1->arr = arr; To show that we want helper_1 to have the maintain its original reference to the array.

    // we are readying helper_2 as argument for quicksort call from left+1 to highIndex on arr.
    helper_2.lowIndex = left + 1;
    helper_2.highIndex = highIndex;
    // we want helper_2 to take the reference of helper_1's arr so that effects of swaps by threads are visible in final answer.
    helper_2.arr = helper_1->arr;

    // spawn a new thread for half the computation of quicksort.
    if (pthread_create(&thread_2, NULL, quicksort, &helper_2) != 0)
    {
        printf("There is an error while creating the thread.");
    }

    quicksort(helper_1);

    if (pthread_join(thread_2, NULL) != 0)
    {
        printf("There is an error while joining the threads.");
    }
}

int partition(int arr[], int lowIndex, int highIndex, int pivot)
{
    int left = lowIndex;
    int right = highIndex - 1;

    while (left < right)
    {
        while (arr[left] <= pivot && left < right)
        {
            left++;
        }

        while (arr[right] >= pivot && left < right)
        {
            right--;
        }

        swap(arr, left, right);
    }

    if (arr[left] > arr[highIndex])
    {
        swap(arr, left, highIndex);
    }
    else
    {
        left = highIndex;
    }
    return left;
}

void swap(int arr[], int left, int right)
{
    int temp = arr[left];
    arr[left] = arr[right];
    arr[right] = temp;
}

int main(int argc, char *argv[])
{

    srand((unsigned int)time(NULL));
    int arr[SIZE];

    // initialise an array with random values.
    for (int i = 0; i < SIZE; i++)
    {
        arr[i] = 1 + rand() % (15 + 1 - 1);
    }

    printf("Before sorting is: ");
    for (int i = 0; i < SIZE; i++)
    {
        printf("%d ", arr[i]);
    }

    // we will use a structure to pass the values to thread's functions.
    struct argument *helper = malloc(sizeof(struct argument));
    helper->arr = malloc(sizeof(int) * SIZE);
    helper->arr = arr;
    helper->lowIndex = 0;
    helper->highIndex = SIZE - 1;

    quicksort(helper);

    printf("\nAfter sorting is: ");
    for (int i = 0; i < SIZE; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");
    return 0;
}
