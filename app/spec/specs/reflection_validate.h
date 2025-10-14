#include "../spec.h"

static struct {
  bool fail;
  bool validator_called;
} sim;

void example_validator (
    void* target,
    struct reflection* reflection
)
{
  sim.validator_called = true;
  if (sim.fail)
    fail("fail fast and hard");
}
