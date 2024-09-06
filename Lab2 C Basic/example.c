/*
 *   McGill ECSE427/COMP310 Lab2 C Basic Example
 *   Created by: Jason Zixu Zhou (all rights reserved)
 *
 *   Important Notes:
 *   1. Avoid using "magic numbers" (e.g., assuming `int` is always 4 bytes).
 *   2. Use standard libraries like `stdint.h` for fixed-width integer types to ensure consistency across different platforms.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h> // Standard library for fixed-width integer types
#include <limits.h>
#include <float.h>

// Variables and Data Types
// Function to explore different types of variables in C
void exploreDataTypes()
{
    printf("Introduction to Data Types\n\n");

    // Declaring and initializing different basic data types
    char aChar = 'W';                   // Character variable
    int anInteger = 1024;               // Integer variable
    long aLong = 123456789L;            // Long integer for large values
    float aFloat = 3.14159f;            // Floating point variable for decimal numbers
    double aDouble = 2.718281828459045; // Double precision floating point variable

    printf("Character: %c, Integer: %d, Long: %ld, Float: %f, Double: %f\n",
           aChar, anInteger, aLong, aFloat, aDouble);

    // Fixed-width integer types using stdint.h for portability
    int8_t smallInt = 127;                        // 8-bit signed integer
    int16_t mediumInt = 32767;                    // 16-bit signed integer
    int32_t largeInt = 2147483647;                // 32-bit signed integer
    int64_t veryLargeInt = 9223372036854775807LL; // 64-bit signed integer

    printf("Fixed-width Integers: int8_t: %d, int16_t: %d, int32_t: %d, int64_t: %lld\n",
           smallInt, mediumInt, largeInt, veryLargeInt);

    // Exploring strings and arrays
    char string[] = "Hello, C!"; // String literal
    int numbers[3] = {1, 2, 3};  // Integer array with 3 elements

    printf("String: %s, Numbers: %d, %d, %d\n", string, numbers[0], numbers[1], numbers[2]);
}

// Control Structures
// Function to demonstrate the use of control structures like if-else, switch, and loops
void exploreControlStructures()
{
    printf("Control Structures\n\n");

    // Example of if-else control structure
    int age = 19;
    if (age >= 18)
    {
        printf("Adult\n"); // If age is 18 or more, it's an adult
    }
    else
    {
        printf("Minor\n"); // Otherwise, it's a minor
    }

    // Example of switch control structure
    int day = 5; // Variable representing a day of the week
    switch (day)
    {
    case 1:
        printf("Monday\n");
        break;
    case 2:
        printf("Tuesday\n");
        break;
    case 3:
        printf("Wednesday\n");
        break;
    case 4:
        printf("Thursday\n");
        break;
    case 5:
        printf("Friday\n");
        break;
    case 6:
        printf("Saturday\n");
        break;
    case 7:
        printf("Sunday\n");
        break;
    default:
        printf("Invalid day\n"); // Default case if day is not between 1 and 7
    }

    // Example of a for loop
    for (int i = 0; i < 5; i++) // Loop from 0 to 4
    {
        printf("i = %d\n", i); // Print the value of i in each iteration
    }
}

// Functions
// Simple function to add two integers
int add(int x, int y)
{
    return x + y; // Return the sum of x and y
}

// Function demonstrating how to call other functions in C
void demonstrateFunctions()
{
    printf("Function: 5 + 3 = %d\n", add(5, 3)); // Call add() function and print the result
}

// Pointers and Memory Management
// Function to demonstrate the use of pointers and dynamic memory allocation
void explorePointersAndMemory()
{
    int x = 10;    // Declare an integer variable
    int *ptr = &x; // Declare a pointer to x (stores the address of x)

    // Print the value of x and the value stored at the pointer (dereferenced)
    printf("x = %d, *ptr = %d\n", x, *ptr);

    // Dynamic memory allocation using malloc()
    int *dynamicArray = (int *)malloc(3 * sizeof(int)); // Allocate memory for an array of 3 integers
    if (dynamicArray != NULL)                           // Check if malloc succeeded
    {
        // Initialize and print the dynamically allocated array
        for (int i = 0; i < 3; i++)
        {
            dynamicArray[i] = i * 10; // Assign value to each element
            printf("dynamicArray[%d] = %d\n", i, dynamicArray[i]);
        }
        free(dynamicArray); // Free the dynamically allocated memory
    }
}

// Structs and Unions
// Function to demonstrate the use of structs and unions in C
void exploreStructsAndUnions()
{
    // Define and initialize a struct called Person
    struct Person
    {
        char name[50];           // Field to store the person's name
        int age;                 // Field to store the person's age
    } person = {"John Doe", 30}; // Create an instance of Person with values

    // Print the struct's fields
    printf("Person: %s, Age: %d\n", person.name, person.age);

    // Define a union that can store either an int or a float
    union Data
    {
        int intVal;     // Integer field
        float floatVal; // Float field
    } data;

    // Assign a value to the integer field of the union
    data.intVal = 5;
    printf("Union intVal: %d\n", data.intVal); // Print the integer value

    // Assign a value to the float field (overwrites the integer value)
    data.floatVal = 3.14f;
    printf("Union floatVal: %f\n", data.floatVal); // Print the float value
}

// Main function: Entry point of the program
int main()
{
    exploreDataTypes();         // Call function to explore basic data types
    exploreControlStructures(); // Call function to demonstrate control structures
    demonstrateFunctions();     // Call function to demonstrate function usage
    explorePointersAndMemory(); // Call function to explore pointers and memory management
    exploreStructsAndUnions();  // Call function to demonstrate structs and unions

    return 0; // Indicate successful completion
}
