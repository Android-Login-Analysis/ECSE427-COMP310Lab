// Exercise: Write a function that takes two integers
// as parameters and returns their sum.
// Call this function from the main function and print the result.
#include <stdio.h>

int add(int a, int b)
{
    return a + b;
}

int main()
{
    int result = add(10, 20);
    printf("Sum: %d\n", result);
    return 0;
}
