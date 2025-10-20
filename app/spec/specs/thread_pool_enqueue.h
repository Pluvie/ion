#include "../spec.h"

static struct {
  int results[3];
} sim;

void example_work_enqueue (
    void* sleep_ptr
)
{
  int number = *(int*) sleep_ptr;
  sleep(number*SECONDS);
  sim.results[number-1] = number;
}
