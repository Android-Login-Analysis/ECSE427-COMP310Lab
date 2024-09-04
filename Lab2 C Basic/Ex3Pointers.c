// Exercise: Write a program that creates an integer variable.
// Use a pointer to change the value of the integer
// and then print it using the pointer.
#include <stdio.h>

int main()
{
    int num = 10;
    int *p = &num;
    *p = 20; // Changing the value of num through the pointer

    printf("Changed value: %d\n", *p);
    return 0;
}
