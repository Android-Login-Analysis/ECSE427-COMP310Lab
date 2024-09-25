#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n;
    int *p;
    while (1)
    {
        scanf("%d", &n);
        p = malloc(sizeof(int) * n);
        while (n > 0)
        {
            *p = 0;
            p++;
            n--;
        }
    }
    return 0;
}
