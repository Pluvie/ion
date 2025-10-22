#include "../spec.h"

#if standard(>= C11)
static void example_work (
    void* sleep_ptr
)
{
  int number = *(int*) sleep_ptr;
  sleep(number);
}
#endif
