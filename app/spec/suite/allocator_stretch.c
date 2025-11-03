#include "allocator_stretch.h"

spec( allocator_stretch ) {
  argument(struct allocator* allocator);
  argument(uint amount);
  returns(byte* result);

  precondition("a valid, previously initialized allocator");
  #define preconditions \
    initialized_allocator = allocator_init(32); \
    allocator = &initialized_allocator;

  when("the line has no previous data") {
    when("the amount is not greater than the line capacity") {
      amount = 16;
      apply(preconditions);
      result = allocator_stretch(allocator, amount);

      must("increase the line position by the requested amount");
        verify(allocator->line.position == amount);
      must("return a valid memory address");
        verify(result >= allocator->line.data);
        verify(result <= allocator->line.data + allocator->line.capacity);

      success();
        allocator_release(allocator);
    } end();

    when("the amount is greater than the line capacity") {
      amount = 50;
      apply(preconditions);
      result = allocator_stretch(allocator, amount);

      must("increase the line capacity to the next power of two of the amount");
        verify(allocator->line.capacity == next_pow2(amount));
      must("increase the line position");
        verify(allocator->line.position == amount);
      must("return a valid memory address");
        verify(result >= allocator->line.data);
        verify(result <= allocator->line.data + allocator->line.capacity);

      success();
        allocator_release(allocator);
    } end();
  } end();

  when("the line has previous data") {
    #define previous_data_condition \
      allocator_stretch(allocator, 16);
    int previous_allocator_capacity;
    int previous_allocator_position;

    when("the amount is not greater than the remaining line space") {
      amount = 8;
      apply(preconditions);
      apply(previous_data_condition);

      previous_allocator_position = allocator->line.position;
      result = allocator_stretch(allocator, amount);

      must("increase the line position by the requested amount");
        verify(allocator->line.position == previous_allocator_position + amount);
      must("return a valid memory address");
        verify(result >= allocator->line.data);
        verify(result <= allocator->line.data + allocator->line.capacity);

      success();
        allocator_release(allocator);
    } end();

    when("the amount is greater than the line remaining space") {
      when("the amount is not greater than two times the current line capacity") {
        amount = 24;

        apply(preconditions);
        apply(previous_data_condition);

        previous_allocator_capacity = allocator->line.capacity;
        previous_allocator_position = allocator->line.position;
        result = allocator_stretch(allocator, amount);

        must("double the line capacity");
          verify(allocator->line.capacity == 2*previous_allocator_capacity);
        must("increase the line position");
          verify(allocator->line.position == previous_allocator_position + amount);
        must("return a valid memory address");
          verify(result >= allocator->line.data);
          verify(result <= allocator->line.data + allocator->line.capacity);

        success();
          allocator_release(allocator);
      } end();

      when("the amount is greater than two times the current line capacity") {
        amount = 80;

        apply(preconditions);
        apply(previous_data_condition);

        previous_allocator_position = allocator->line.position;
        result = allocator_stretch(allocator, amount);

        must("increase the line capacity to the next power of two of the amount");
          verify(allocator->line.capacity == next_pow2(amount));
        must("increase the line position");
          verify(allocator->line.position == previous_allocator_position + amount);
        must("return a valid memory address");
          verify(result >= allocator->line.data);
          verify(result <= allocator->line.data + allocator->line.capacity);

        success();
          allocator_release(allocator);
      } end();

    } end();
  } end();
}
