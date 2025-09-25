#include "memory_resize.h"

spec( memory_resize ) {
  argument(void* address);
  argument(unsigned int amount);

  precondition("a valid, previously acquired memory address");
    #define preconditions \
      address = memory_acquire(32);

  when("the amount is zero") {
    amount = 0;
    apply(preconditions);
    memory_resize(address, amount);

    must("fatally fail with a specific message");
      verify(eq(sim.fatal, "memory_resize: amount must not be zero"));

    success();
      memory_release(address);
  } end();

  when("the amount is greater than zero") {
    amount = 64;

    when("the realloc function fails") {
      sim.realloc = nullptr;
      apply(preconditions);
      memory_resize(address, amount);

      must("fatally fail with a specific message");
        verify(eq(sim.fatal, "memory_resize: not enough memory"));

      success();
        memory_release(address);
    } end();

    when("the realloc function succeeds") {
      sim.realloc = (void*) 0x77;
      apply(preconditions);
      void* result = memory_resize(address, amount);

      must("not fail");
        verify(sim.fatal == nullptr);
      must("return the allocated address");
        verify(result == sim.realloc);

      success();
        memory_release(address);
    } end();
  } end();

  #undef preconditions
}
