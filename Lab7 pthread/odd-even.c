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
    while (1)
    {
        printf("true");
    }
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
    int arr[SIZE];
    // Initialize the array with random values.
    for (int i = 0; i < SIZE; i++)
    {
        arr[i] = 1 + rand() % (30 + 1 - 1);
        printf("%d ", arr[i]);
    }
    printf("\n");

    struct tracker *output = malloc(sizeof(struct tracker));
    if (!output)
    {
        fprintf(stderr, "Memory allocation failed for output.\n");
        return -1;
    }

    // No need to allocate memory for output->arr, directly point to arr
    output->arr = arr;
    output->evenSum = 0;
    output->oddSum = 0;

    // Initialize mutex
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        fprintf(stderr, "Mutex initialization failed.\n");
        free(output);
        return -1;
    }

    // Initialize condition variable
    if (pthread_cond_init(&cond, NULL) != 0)
    {
        fprintf(stderr, "Condition variable initialization failed.\n");
        pthread_mutex_destroy(&lock);
        free(output);
        return -1;
    }

    pthread_t thread[2];

    // Create thread 0 (evenWorker)
    if (pthread_create(&thread[0], NULL, evenWorker, output) != 0)
    {
        fprintf(stderr, "Failed to create evenWorker thread.\n");
        pthread_mutex_destroy(&lock);
        pthread_cond_destroy(&cond);
        free(output);
        return -1;
    }

    // Create thread 1 (oddWorker)
    if (pthread_create(&thread[1], NULL, oddWorker, output) != 0)
    {
        fprintf(stderr, "Failed to create oddWorker thread.\n");
        pthread_cancel(thread[0]); // Cancel the first thread if second thread creation fails
        pthread_mutex_destroy(&lock);
        pthread_cond_destroy(&cond);
        free(output);
        return -1;
    }

    // pthread_join(thread[0], NULL);
    // pthread_join(thread[1], NULL);

    printf("Output from thread 0 (evenWorker) is:%d\n", output->evenSum);
    printf("Output from thread 1 (oddWorker) is:%d\n", output->oddSum);

    // Cleanup
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
    free(output); // No need to free output->arr because it's not dynamically allocated

    return 0;
}
