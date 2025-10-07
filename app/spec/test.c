#include <stdio.h>

int main (
    int argc,
    char** argv
)
{
  char* s1 = "2147483647";
  char* s2 = "9999999999";

  int n1 = 0;
  int n2 = 0;
  for (int i = 0; i < 10; i++) {
    printf("\n");
    printf("[i]: %i, [c]: %c", i, s1[i]);
    printf(">> %i \n", n1);
    n1 = (10 * n1) + (s1[i] - '0');
    printf(">> %i \n", n1);
  }

  printf("-------------------\n");
  printf("-------------------\n");
  for (int i = 0; i < 10; i++) {
    printf("\n");
    printf("[i]: %i, [c]: %c", i, s2[i]);
    printf(">> %i \n", n2);
    n2 = (10 * n2) + (s2[i] - '0');
    printf(">> %i \n", n2);
  }

  printf("n1: %i, bc: %i\n", n1, __builtin_clz(n1));
  printf("n1: %i, bc: %i\n", n2, __builtin_clz(n2));

  return 0;
}
