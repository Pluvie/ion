#include "../spec.h"

static void example_work (
    void* sleep_ptr
)
{
  int number = *(int*) sleep_ptr;
  sleep(number);
}
