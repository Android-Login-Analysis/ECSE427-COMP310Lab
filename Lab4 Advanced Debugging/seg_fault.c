#include <stdio.h>

// dereference a NULL pointer
int main()
{
    int *ptr = NULL;
    printf("%d\n", *ptr); // Causes segmentation fault
    return 0;
}
