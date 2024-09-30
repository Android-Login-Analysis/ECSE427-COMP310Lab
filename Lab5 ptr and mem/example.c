#include <stdio.h>
#include <stdlib.h>

int main()
{
    // Allocate memory for 10 integers
    int *p = malloc(10 * sizeof(int));
    if (p == NULL)
    {
        printf("Initial malloc failed.\n");
        return 1;
    }

    // Use the allocated memory (initialize the array)
    for (int i = 0; i < 10; i++)
    {
        p[i] = i + 1;
    }

    // Reallocate memory for 20 integers
    int *temp = realloc(p, 20 * sizeof(int));
    if (temp == NULL)
    {
        // If realloc fails, the original memory is still valid
        printf("Realloc failed, original memory is still valid.\n");
        free(p); // Free the original memory
        return 1;
    }

    // If realloc is successful, use the new pointer
    p = temp;

    // Initialize the new part of the array
    for (int i = 10; i < 20; i++)
    {
        p[i] = i + 1;
    }

    // Print the array to verify
    for (int i = 0; i < 20; i++)
    {
        printf("%d ", p[i]);
    }
    printf("\n");

    // Free the reallocated memory
    free(p);

    return 0;
}
