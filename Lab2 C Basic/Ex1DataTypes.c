// Exercise: Write a program that declares and initializes various
// basic data types such as an integer, a float, a double,
// and a character. Then, print their values.
#include <stdio.h>

int main()
{
    int myInt = 50;
    float myFloat = 5.99f;
    double myDouble = 3.14159;
    char myChar = 'A';

    printf("Integer: %d\nFloat: %.2f\nDouble: %.5f\nCharacter: %c\n", myInt, myFloat, myDouble, myChar);
    return 0;
}
