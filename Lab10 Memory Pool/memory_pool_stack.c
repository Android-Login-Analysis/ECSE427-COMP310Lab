#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define POOL_SIZE 100000       // Define the total number of blocks available in the memory pool.
#define BLOCK_SIZE 32          // Size of each block in bytes.
#define NUM_ALLOCATIONS 100000 // Number of allocations and deallocations to perform in the test.

// Define a structure to represent each block in the memory pool.
typedef struct
{
    char data[BLOCK_SIZE];
} Block;

Block pool[POOL_SIZE];     // Array to hold the memory blocks.
int free_index[POOL_SIZE]; // Stack to keep track of free block indices.
int stack_top = -1;        // Variable to indicate the top of the stack.

// Initialize the memory pool and the free index stack.
void init_pool()
{
    // Loop to initialize each index in the free index stack.
    for (int i = 0; i < POOL_SIZE; i++)
    {
        free_index[i] = i; // Each stack entry corresponds to a block index in the pool.
    }
    stack_top = POOL_SIZE - 1; // Set the top of the stack to the last index.
}

// Function to allocate a block from the memory pool using a stack-based free list.
void *pool_malloc()
{
    // Check if there are any blocks left in the pool.
    if (stack_top == -1)
    {
        return NULL; // If no blocks are available, return NULL.
    }
    // Pop the top index from the stack to get the next available block.
    int index = free_index[stack_top--]; // Decrease stack top and get the free index.
    return &pool[index];                 // Return a pointer to the allocated block.
}

// Function to free a block and return it to the pool.
void pool_free(void *ptr)
{
    // Calculate the block's index in the pool array based on the pointer address.
    int index = ((Block *)ptr - pool);
    // Validate the index to prevent out-of-bounds behavior.
    if (index < 0 || index >= POOL_SIZE)
    {
        printf("Invalid free request\n");
        return;
    }
    // Push the freed block's index back onto the stack.
    free_index[++stack_top] = index; // Increment stack top and store the index.
}

int main()
{
    init_pool(); // Initialize the pool and the index stack.
    void *ptrs[NUM_ALLOCATIONS];
    clock_t start, end;

    // Test memory allocation and deallocation using the memory pool.
    start = clock();
    for (int i = 0; i < NUM_ALLOCATIONS; i++)
    {
        ptrs[i] = pool_malloc(); // Allocate blocks using the memory pool.
    }
    for (int i = 0; i < NUM_ALLOCATIONS; i++)
    {
        pool_free(ptrs[i]); // Free the allocated blocks.
    }
    end = clock();
    printf("Memory pool time: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Test memory allocation and deallocation using standard malloc/free for comparison.
    start = clock();
    for (int i = 0; i < NUM_ALLOCATIONS; i++)
    {
        ptrs[i] = malloc(BLOCK_SIZE);
    }
    for (int i = 0; i < NUM_ALLOCATIONS; i++)
    {
        free(ptrs[i]);
    }
    end = clock();
    printf("Malloc time: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}
