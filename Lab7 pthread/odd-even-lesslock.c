#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define SIZE 100       // Define the size of the array
#define THREAD_COUNT 4 // Define the number of threads to be created

// Mutex locks to protect shared resources (evenSum and oddSum)
pthread_mutex_t evenSumLock;
pthread_mutex_t oddSumLock;

// Structure to hold array data and sum results for each thread
struct tracker
{
    int *arr;    // Pointer to the array to be processed
    int evenSum; // Sum of odd numbers from even-indexed elements
    int oddSum;  // Sum of even numbers from odd-indexed elements
    int start;   // Start index for the thread to process
    int end;     // End index for the thread to process
};

// Worker function for each thread
// This function processes a specific portion of the array based on its assigned range
void *worker(void *arg)
{
    struct tracker *output = arg; // Cast the argument to the tracker structure
    int localEvenSum = 0;         // Local variable to store the sum of odd numbers at even indices
    int localOddSum = 0;          // Local variable to store the sum of even numbers at odd indices

    // Iterate over the assigned range of the array (from start to end)
    for (int i = output->start; i < output->end; i++)
    {
        // Check if the index is even
        if (i % 2 == 0) // Even index
        {
            // Check if the value at the even index is odd
            if (output->arr[i] % 2 != 0) // Odd value at an even index
            {
                localEvenSum += output->arr[i]; // Accumulate the odd value into the localEvenSum
            }
        }
        else // Odd index
        {
            // Check if the value at the odd index is even
            if (output->arr[i] % 2 == 0) // Even value at an odd index
            {
                localOddSum += output->arr[i]; // Accumulate the even value into the localOddSum
            }
        }
    }

    // Lock the evenSum mutex to safely update the shared evenSum variable
    // pthread_mutex_lock(&evenSumLock);
    output->evenSum += localEvenSum; // Add the localEvenSum to the shared evenSum
    // pthread_mutex_unlock(&evenSumLock); // Unlock the mutex after updating

    // Lock the oddSum mutex to safely update the shared oddSum variable
    // pthread_mutex_lock(&oddSumLock);
    output->oddSum += localOddSum; // Add the localOddSum to the shared oddSum
    // pthread_mutex_unlock(&oddSumLock); // Unlock the mutex after updating

    // Exit the thread after finishing processing the assigned portion of the array
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    int arr[SIZE];                        // Array to hold random values
    pthread_t threads[THREAD_COUNT];      // Array of threads
    struct tracker outputs[THREAD_COUNT]; // Array to store tracker structures for each thread

    // Initialize the array with random values between 1 and 30
    for (int i = 0; i < SIZE; i++)
    {
        arr[i] = 1 + rand() % 30;
        printf("%d ", arr[i]); // Print the array for debugging purposes
    }
    printf("\n");

    // Initialize mutex locks to protect evenSum and oddSum
    pthread_mutex_init(&evenSumLock, NULL);
    pthread_mutex_init(&oddSumLock, NULL);

    // Determine the chunk size each thread will process
    int chunkSize = SIZE / THREAD_COUNT;

    // Create THREAD_COUNT threads and assign each one a portion of the array
    for (int i = 0; i < THREAD_COUNT; i++)
    {
        outputs[i].arr = arr;                                                           // Pass the array to the tracker structure
        outputs[i].evenSum = 0;                                                         // Initialize the evenSum for this thread
        outputs[i].oddSum = 0;                                                          // Initialize the oddSum for this thread
        outputs[i].start = i * chunkSize;                                               // Calculate the start index for this thread
        outputs[i].end = (i == THREAD_COUNT - 1) ? SIZE : outputs[i].start + chunkSize; // Calculate the end index for this thread

        // Create a new thread to process its assigned portion of the array
        if (pthread_create(&threads[i], NULL, worker, &outputs[i]) != 0)
        {
            fprintf(stderr, "Error creating thread %d\n", i); // Print an error message if thread creation fails
            return -1;                                        // Exit with an error code
        }
    }

    int totalEvenSum = 0; // Variable to store the total sum of odd numbers from even-indexed elements
    int totalOddSum = 0;  // Variable to store the total sum of even numbers from odd-indexed elements

    // Wait for all threads to finish and collect their results
    for (int i = 0; i < THREAD_COUNT; i++)
    {
        pthread_join(threads[i], NULL);     // Wait for thread i to finish
        totalEvenSum += outputs[i].evenSum; // Add this thread's evenSum to the total
        totalOddSum += outputs[i].oddSum;   // Add this thread's oddSum to the total
    }

    // Print the final results
    printf("Total even indexed odd sum: %d\n", totalEvenSum);
    printf("Total odd indexed even sum: %d\n", totalOddSum);

    // Clean up and destroy mutex locks
    pthread_mutex_destroy(&evenSumLock);
    pthread_mutex_destroy(&oddSumLock);

    return 0; // Exit the program successfully
}
