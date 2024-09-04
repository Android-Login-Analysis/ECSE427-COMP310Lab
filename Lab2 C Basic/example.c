/*
 *   McGill ECSE427/COMP310 Lab2 C Basic Example
 *   Created by: Jason Zixu Zhou (all rights reserved)
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <float.h>

// Variables and Data Types
void exploreDataTypes()
{
    printf("Introduction to Data Types\n\n");

    char aChar = 'W';                   // Character variable
    int anInteger = 1024;               // Integer variable
    long aLong = 123456789L;            // Long integer
    float aFloat = 3.14159f;            // Floating point variable
    double aDouble = 2.718281828459045; // Double precision floating point variable

    printf("Character: %c, Integer: %d, Long: %ld, Float: %f, Double: %f\n",
           aChar, anInteger, aLong, aFloat, aDouble);

    // Exploring strings and arrays
    char string[] = "Hello, C!";
    int numbers[3] = {1, 2, 3};

    printf("String: %s, Numbers: %d, %d, %d\n", string, numbers[0], numbers[1], numbers[2]);
}

// Control Structures
void exploreControlStructures()
{
    printf("Control Structures\n\n");

    // If-Else
    int age = 19;
    if (age >= 18)
    {
        printf("Adult\n");
    }
    else
    {
        printf("Minor\n");
    }

    // Switch
    int day = 5;
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
        printf("Invalid day\n");
    }

    // Loops
    for (int i = 0; i < 5; i++)
    {
        printf("i = %d\n", i);
    }
}

// Functions

// Function declaration
int add(int x, int y)
{
    return x + y;
}
void demonstrateFunctions()
{
    printf("Function: 5 + 3 = %d\n", add(5, 3));
}

// Pointers and Memory Management
void explorePointersAndMemory()
{
    int x = 10;
    int *ptr = &x;

    printf("x = %d, *ptr = %d\n", x, *ptr);

    int *dynamicArray = (int *)malloc(3 * sizeof(int));
    if (dynamicArray != NULL)
    {
        for (int i = 0; i < 3; i++)
        {
            dynamicArray[i] = i * 10;
            printf("dynamicArray[%d] = %d\n", i, dynamicArray[i]);
        }
        free(dynamicArray);
    }
}

// Structs and Unions
void exploreStructsAndUnions()
{
    struct Person
    {
        char name[50];
        int age;
    } person = {"John Doe", 30};

    printf("Person: %s, Age: %d\n", person.name, person.age);

    union Data
    {
        int intVal;
        float floatVal;
    } data;

    data.intVal = 5;
    printf("Union intVal: %d\n", data.intVal);
    data.floatVal = 3.14f;
    printf("Union floatVal: %f\n", data.floatVal);
}

int main()
{
    exploreDataTypes();
    exploreControlStructures();
    demonstrateFunctions();
    explorePointersAndMemory();
    exploreStructsAndUnions();

    return 0;
}
