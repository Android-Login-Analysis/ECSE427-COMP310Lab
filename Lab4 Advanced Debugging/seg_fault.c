#include <stdio.h>

int main()
{
    int *ptr = NULL;
    printf("%d\n", *ptr); // Causes segmentation fault
    return 0;
}
