#include "memory_acquire_aligned.h"

spec( memory_acquire_aligned ) {
  argument(unsigned int amount);
  argument(unsigned int alignment);

  when("the amount is zero") {
    amount = 0;
    alignment = 0;
    memory_acquire_aligned(amount, alignment);

    must("fatally fail with a specific message");
      verify(cstreq(sim.fatal, "memory_acquire_aligned: amount must not be zero"));

    success();
  } end();

  when("the amount is greater than zero") {
    amount = 32;

    when("the alignment is not a power of two") {
      alignment = 17;

      when("the memory allocation fails") {
        sim.allocation_fails = true;
        memory_acquire_aligned(amount, alignment);

        must("fatally fail with a specific message");
          verify(cstreq(sim.fatal, "memory_acquire_aligned: not enough memory"));

        success();
      } end();

      when("the memory allocation succeeds") {
        sim.allocation_fails = false;
        void* result = memory_acquire_aligned(amount, alignment);

        must("not fail");
          verify(sim.fatal == nullptr);
        must("return the allocated address with alignment changed to its next power of two");
          verify((unsigned int) result % next_pow2(alignment) == 0);

        success();
      } end();
    } end();

    when("the alignment is a power of two") {
      alignment = 64;

      when("the memory allocation fails") {
        sim.allocation_fails = true;
        memory_acquire_aligned(amount, alignment);

        must("fatally fail with a specific message");
          verify(cstreq(sim.fatal, "memory_acquire_aligned: not enough memory"));

        success();
      } end();

      when("the memory allocation succeeds") {
        sim.allocation_fails = false;
        void* result = memory_acquire_aligned(amount, alignment);

        must("not fail");
          verify(sim.fatal == nullptr);
        must("return the allocated address with the given alignment");
          verify((unsigned int) result % alignment == 0);

        success();
      } end();
    } end();
  } end();
}
