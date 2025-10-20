#include "../spec.h"

static struct {
  void* unused;
} sim;

void example_work (
    void* sleep_ptr
)
{
  printl("Doing some work");
  sleep((*(int*) sleep_ptr)*SECONDS);
  printl("Work completed");
}
