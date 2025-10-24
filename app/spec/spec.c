#include <ion.h>
#include <ion.c>

int main (
    int argc,
    char** argv
)
{
  printf("HELLO WORLD! number: {%"INT_T__FORMAT"}\n", 42L);
  return EXIT_SUCCESS;
}
