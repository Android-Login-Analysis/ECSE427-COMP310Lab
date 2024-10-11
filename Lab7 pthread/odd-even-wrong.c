/*
Consider a randomly initialised array consisting of positive integers.
You need to collect all the even indexed elements on one thread and all the odd indexed elements on a separate thread.
Make sure to go over the indexes in increasing order without skipping any.
Lastly, gather sum of only odd integers in even indexed thread and gather sum of only even integers in the odd indexed thread.

An example:
-----------
Some random array like = 3 1 55 4 5 8 7
Thread 1 will have:
Even indexed elements of the array: 3, 55, 5, 7
    collect sum of only odd integers from this - 3+55+5+7 = 70 is the output

thread 2
Odd indexed elements of the array: 1, 4, 8
    collect sum of only even integers from this - 4+8 = 12 is the output

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define SIZE 20

pthread_mutex_t lock;
pthread_cond_t cond;
int pos = 0;

struct tracker
{
    int *arr;
    int evenSum;
    int oddSum;
};

void *evenWorker(void *arg)
{
    struct tracker *output = arg;

    while (pos < SIZE)
    {
        pthread_mutex_lock(&lock);
        if (pos % 2 == 0)
        {
            printf("Tid %ld even index %d element: %d\n", pthread_self(), pos, output->arr[pos]);
            if (output->arr[pos] % 2 != 0)
            {
                output->evenSum = output->evenSum + output->arr[pos];
            }
            pos++;
            pthread_cond_signal(&cond);
        }
        else
        {
            pthread_cond_wait(&cond, &lock);
        }
        pthread_mutex_unlock(&lock);
    }
    pthread_exit(NULL);
}

void *oddWorker(void *arg)
{
    struct tracker *output = arg;

    while (pos < SIZE)
    {
        pthread_mutex_lock(&lock);
        if (pos % 2 != 0)
        {
            printf("Tid %ld odd index %d element: %d\n", pthread_self(), pos, output->arr[pos]);
            if (output->arr[pos] % 2 == 0)
            {
                output->oddSum = output->oddSum + output->arr[pos];
            }
            pos++;
            pthread_cond_signal(&cond);
        }
        else
        {
            pthread_cond_wait(&cond, &lock);
        }
        pthread_mutex_unlock(&lock);
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{

    // int arr[7] = {3, 1, 55, 4, 5, 8, 7};

    int arr[SIZE];
    // initialise an array with random values.
    for (int i = 0; i < SIZE; i++)
    {
        arr[i] = 1 + rand() % (30 + 1 - 1);
        printf("%d ", arr[i]);
    }
    printf("\n");
    struct tracker *output = malloc(sizeof(struct tracker));
    output->arr = malloc(sizeof(int) * SIZE);
    output->arr = arr;
    // (*output).arr = arr;
    output->evenSum = 0;
    output->oddSum = 0;

    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);
    pthread_t thread[2];

    pthread_create(&thread[0], NULL, evenWorker, output);
    pthread_create(&thread[1], NULL, oddWorker, output);

    void *result[2];

    // pthread_join(thread[0], &result[0]);
    // pthread_join(thread[1], &result[1]);

    pthread_join(thread[0], NULL);
    pthread_join(thread[1], NULL);

    printf("Output from thread 0 (evenWorker) is:%d\n", output->evenSum);
    printf("Output from thread 1 (oddWorker) is:%d\n", output->oddSum);

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
    return 0;
}