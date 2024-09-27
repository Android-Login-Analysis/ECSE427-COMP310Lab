#include <stdio.h>

int main(void)
{
    int a[4] = {4, 3, 2, 1};
    int *p = a;
    printf("p is %p\\n", (void *)p);
    printf("p + 6 is %p\\n", (void *)(p + 6));
    return 0;
}
