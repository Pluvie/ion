#include "memory_acquire.h"

spec( memory_acquire ) {
  argument(unsigned int amount);

  when("the amount is zero") {
    amount = 0;
    memory_acquire(amount);

    must("fatally fail with a specific message");
      verify(strcmp(sim.fatal, "memory_acquire: amount must not be zero") == 0);

    success();
  } end();

  when("the amount is greater than zero") {
    amount = 32;

    when("the malloc function fails") {
      sim.malloc = nullptr;
      memory_acquire(amount);

      must("fatally fail with a specific message");
        verify(strcmp(sim.fatal, "memory_acquire: not enough memory") == 0);

      success();
    } end();

    when("the malloc function succeeds") {
      sim.malloc = (void*) 0x77;
      void* result = memory_acquire(amount);

      must("not fail");
        verify(sim.fatal == nullptr);
      must("return the allocated address");
        verify(result == sim.malloc);

      success();
    } end();
  } end();
}
