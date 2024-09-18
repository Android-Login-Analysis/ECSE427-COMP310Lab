#include <stdlib.h>

void leak_memory()
{
    int *ptr = malloc(sizeof(int));
    *ptr = 10; // Memory leak occurs here
}

int main()
{
    leak_memory();
    return 0;
}
