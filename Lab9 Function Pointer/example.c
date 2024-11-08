#include <stdio.h>

// Declaration of a function pointer type that takes two integers and returns an integer
typedef int (*operation)(int, int);

// Function to add two integers
int add(int x, int y)
{
    return x + y;
}

// Function to subtract the second integer from the first
int sub(int x, int y)
{
    return x - y;
}

// Function that takes function pointer as an argument and applies it to the given integers
void apply(int a, int b, operation op)
{
    int result = op(a, b); // Using the function pointer to call the function
    printf("Result: %d\n", result);
}

// Main function
int main()
{
    // Initialize function pointers with the addresses of 'add' and 'sub'
    operation op_add = add;
    operation op_sub = sub;

    // Array of function pointers
    operation ops[2] = {add, sub};

    // Using the function pointer to call 'add' directly
    printf("Direct call to add: %d\n", op_add(5, 3));

    // Using the function pointer to call 'sub' directly
    printf("Direct call to sub: %d\n", op_sub(5, 3));

    // Using the apply function to execute 'add' via a function pointer
    apply(7, 2, op_add);

    // Using the apply function to execute 'sub' via a function pointer
    apply(7, 2, op_sub);

    // Using function pointer array to call 'add'
    printf("Using function pointer array, add: %d\n", ops[0](10, 5));

    // Using function pointer array to call 'sub'
    printf("Using function pointer array, sub: %d\n", ops[1](10, 5));

    return 0;
}
