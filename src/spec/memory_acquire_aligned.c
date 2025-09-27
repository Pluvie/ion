#include "memory_acquire_aligned.h"

spec( memory_acquire_aligned ) {
  argument(unsigned int amount);
  argument(unsigned int alignment);

  when("the amount is zero") {
    amount = 0;
    alignment = 0;
    memory_acquire_aligned(amount, alignment);

    must("fatally fail with a specific message");
      verify(streq(sim.fatal, "memory_acquire_aligned: amount must not be zero"));

    success();
  } end();

  when("the amount is greater than zero") {
    amount = 32;

    when("the alignment is not a power of two") {
      alignment = 17;

      memory_acquire_aligned(amount, alignment);

      must("change the alignment to its next power of two");
        verify(sim.aligned_alloc.alignment == next_pow2(alignment));

      success();
    } end();

    when("the alignment is a power of two") {
      alignment = 64;

      when("the aligned_alloc function fails") {
        sim.aligned_alloc.result = nullptr;
        memory_acquire_aligned(amount, alignment);

        must("fatally fail with a specific message");
          verify(streq(sim.fatal, "memory_acquire_aligned: not enough memory"));

        success();
      } end();

      when("the aligned_alloc function succeeds") {
        sim.aligned_alloc.result = (void*) 0x99;
        void* result = memory_acquire_aligned(amount, alignment);

        must("not fail");
          verify(sim.fatal == nullptr);
        must("return the allocated address");
          verify(result == sim.aligned_alloc.result);

        success();
      } end();
    } end();
  } end();
}
