// main.c
#include <stdio.h>
#include "myheader.h"
#include "myheader.h" // Even if this is included twice, #pragma once prevents multiple inclusion!

void myFunction()
{
    printf("Hello from myFunction!\n");
}

void anotherFunction()
{
    printf("Hello from anotherFunction!\n");
}

int main()
{
    myFunction();
    anotherFunction();
    return 0;
}
