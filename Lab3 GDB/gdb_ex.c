#include <stdio.h>

int main()
{
    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
    int e = 5;
    int f = 6;
    int *ptrs[] = {&a, &b, &c, &d, &e, &f};

    int sum = 0;
    for (int i = 0; i < 6; i++)
    {
        sum += *ptrs[i];
        if (i == 3)
            ptrs[5] = NULL;
    }

    printf("Sum of numbers: %d\n", sum);
}