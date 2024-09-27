#include <stdio.h>
#include <stdlib.h>

#define BIGSIZE 10000000

// // Static version
// int main(void)
// {
//   int a[BIGSIZE] = {
//       0,
//   };
//   printf("%d\n", a[BIGSIZE - 1]);
//   return 0;
// }

// Dynamic version
int main(void)
{
  int *a;
  a = calloc(sizeof(int), BIGSIZE);
  printf("%d\n", a[BIGSIZE - 1]);
  return 0;
}
