#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define POOL_SIZE 100000       // Define the size of the memory pool to accommodate enough allocation requests.
#define BLOCK_SIZE 32          // Size of each memory block within the pool.
#define NUM_ALLOCATIONS 100000 // Number of memory allocation requests to simulate.

// Define a structure to represent each block in the memory pool.
typedef struct
{
    char data[BLOCK_SIZE];
} Block;

Block pool[POOL_SIZE];             // Memory pool array consisting of Block elements.
char pool_bitmap[POOL_SIZE] = {0}; // Bitmap array to keep track of which blocks are free or used.

// Function to allocate a block from the memory pool.
void *pool_malloc()
{
    // Iterate through the bitmap to find a free block.
    for (int i = 0; i < POOL_SIZE; i++)
    {
        if (pool_bitmap[i] == 0)
        {                       // Check if the block is free.
            pool_bitmap[i] = 1; // Mark the block as used.
            return &pool[i];    // Return a pointer to the allocated block.
        }
    }
    return NULL; // Return NULL if the pool is full and no blocks are available.
}

// Function to free a previously allocated block in the memory pool.
void pool_free(void *ptr)
{
    // Calculate the index of the block in the pool array based on the pointer address.
    int index = ((Block *)ptr - pool) / sizeof(Block);
    // Check if the index is within valid range to prevent invalid free requests.
    if (index < 0 || index >= POOL_SIZE)
    {
        printf("Invalid free request\n");
        return;
    }
    pool_bitmap[index] = 0; // Mark the block as free in the bitmap.
}

int main()
{
    void *ptrs[NUM_ALLOCATIONS]; // Array to store pointers to allocated blocks.
    clock_t start, end;          // Variables for timing the performance.

    // Timing memory pool allocation and deallocation.
    start = clock();
    for (int i = 0; i < NUM_ALLOCATIONS; i++)
    {
        ptrs[i] = pool_malloc(); // Allocate block from the pool.
        if (ptrs[i] == NULL)
        { // Check if the allocation was successful.
            printf("Memory pool out of space\n");
            break;
        }
    }
    for (int i = 0; i < NUM_ALLOCATIONS; i++)
    {
        pool_free(ptrs[i]); // Free the allocated blocks.
    }
    end = clock();
    printf("Memory pool time: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Timing standard malloc and free operations for comparison.
    start = clock();
    for (int i = 0; i < NUM_ALLOCATIONS; i++)
    {
        ptrs[i] = malloc(BLOCK_SIZE); // Allocate memory using malloc.
    }
    for (int i = 0; i < NUM_ALLOCATIONS; i++)
    {
        free(ptrs[i]); // Free the allocated memory.
    }
    end = clock();
    printf("Malloc time: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}
