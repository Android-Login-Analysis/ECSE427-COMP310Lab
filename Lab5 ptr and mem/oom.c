#include <stdio.h>
#include <stdlib.h>

int main()
{
    // Pointer to store the allocated memory address
    int *ptr;

    // Infinite loop to keep allocating memory
    while (1)
    {
        // Allocate 1GB of memory each time
        ptr = (int *)malloc(1024 * 1024 * 1024); // 1GB

        // Check if the allocation failed
        // if (ptr == NULL)
        // {
        //     printf("Memory allocation failed!\n");
        //     break;
        // }
        // Print confirmation that 1GB of memory is allocated
        printf("Allocated 1GB of memory\n");
    }

    return 0;
}
