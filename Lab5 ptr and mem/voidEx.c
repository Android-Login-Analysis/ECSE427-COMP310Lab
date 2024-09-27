#include <stdio.h>

int main()
{
    int a = 10;
    char c = 'A';

    int *int_ptr = &a;
    char *char_ptr = &c;

    // No type casting
    printf("Without casting int_ptr: %p\n", int_ptr);
    printf("Without casting char_ptr: %p\n", char_ptr);

    // With type casting
    printf("With casting int_ptr: %p\n", (void *)int_ptr);
    printf("With casting char_ptr: %p\n", (void *)char_ptr);

    return 0;
}
