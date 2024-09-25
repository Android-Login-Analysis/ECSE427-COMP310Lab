#include <stdio.h>

char *myStrcpy(char *dst, char *src);

int main(void)
{
    char x[4] = "123";
    char y[4] = { 'a', 'b', 'c', '\0' };
    myStrcpy(y, x);
    printf("x = %s\ny = %s\n", x, y);
    return 0;
}

char *myStrcpy(char *dst, char *src)
{
    /* Fill the code here! */
}
