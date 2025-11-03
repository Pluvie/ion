#include "allocator_push.h"

spec( allocator_push ) {
  argument(struct allocator* allocator);
  argument(uint amount);
  returns(byte* result);

  precondition("a valid, previously initialized allocator");
  #define preconditions \
    initialized_allocator = allocator_init(32); \
    allocator = &initialized_allocator;

  when("the arena has no previous data") {
    when("the amount is not greater than the arena capacity") {
      amount = 16;
      apply(preconditions);
      result = allocator_push(allocator, amount);

      must("increase the arena position by the requested amount");
        verify(allocator->arena.position == amount);
      must("return a valid memory address");
        verify(result >= allocator->arena.data);
        verify(result <= allocator->arena.data + allocator->arena.capacity);

      success();
        allocator_release(allocator);
    } end();

    when("the amount is greater than the arena capacity") {
      amount = 50;
      apply(preconditions);
      result = allocator_push(allocator, amount);

      must("increase the arena capacity to the next power of two of the amount");
        verify(allocator->arena.capacity == next_pow2(amount));
      must("increase the arena position");
        verify(allocator->arena.position == amount);
      must("return a valid memory address");
        verify(result >= allocator->arena.data);
        verify(result <= allocator->arena.data + allocator->arena.capacity);

      success();
        allocator_release(allocator);
    } end();
  } end();

  when("the arena has previous data") {
    #define previous_data_condition \
      allocator_push(allocator, 16);
    byte* previous_allocator_data;
    int previous_allocator_capacity;
    int previous_allocator_position;

    when("the amount is not greater than the remaining arena space") {
      amount = 8;
      apply(preconditions);
      apply(previous_data_condition);

      previous_allocator_position = allocator->arena.position;
      result = allocator_push(allocator, amount);

      must("increase the arena position by the requested amount");
        verify(allocator->arena.position == previous_allocator_position + amount);
      must("return a valid memory address");
        verify(result >= allocator->arena.data);
        verify(result <= allocator->arena.data + allocator->arena.capacity);

      success();
        allocator_release(allocator);
    } end();

    when("the amount is greater than the arena remaining space") {
      when("the amount is not greater than two times the current arena capacity") {
        amount = 24;

        when("the arena has no regions") {
          apply(preconditions);
          apply(previous_data_condition);
          allocator->arena.regions.addresses = nullptr;
          allocator->arena.regions.count = 0;

          previous_allocator_capacity = allocator->arena.capacity;
          previous_allocator_data = allocator->arena.data;
          result = allocator_push(allocator, amount);

          must("create a region to store the previous arena data");
            verify(allocator->arena.regions.count == 1);
            verify(allocator->arena.regions.addresses != nullptr);
            verify(allocator->arena.regions.addresses[0] == previous_allocator_data);
          must("double the arena capacity");
            verify(allocator->arena.capacity == 2*previous_allocator_capacity);
          must("increase the arena position");
            verify(allocator->arena.position == amount);
          must("return a valid memory address");
            verify(result >= allocator->arena.data);
            verify(result <= allocator->arena.data + allocator->arena.capacity);

          success();
            allocator_release(allocator);
        } end();

        when("the arena has one or more region, less than the regions capacity") {
          apply(preconditions);
          apply(previous_data_condition);
          allocator->arena.regions.count = 4;
          allocator->arena.regions.capacity = 8;
          allocator->arena.regions.addresses = memory_acquire(8*sizeof(void*));
          memory_set(allocator->arena.regions.addresses, 0, 8*sizeof(void*));

          previous_allocator_capacity = allocator->arena.capacity;
          previous_allocator_data = allocator->arena.data;
          result = allocator_push(allocator, amount);

          must("create a region to store the previous arena data");
            verify(allocator->arena.regions.count == 5);
            verify(allocator->arena.regions.addresses[4] == previous_allocator_data);
          must("double the arena capacity");
            verify(allocator->arena.capacity == 2*previous_allocator_capacity);
          must("increase the arena position");
            verify(allocator->arena.position == amount);
          must("return a valid memory address");
            verify(result >= allocator->arena.data);
            verify(result <= allocator->arena.data + allocator->arena.capacity);

          success();
            allocator_release(allocator);
        } end();

        when("the arena has one or more region, equal to the regions capacity") {
          apply(preconditions);
          apply(previous_data_condition);
          allocator->arena.regions.count = 8;
          allocator->arena.regions.capacity = 8;
          allocator->arena.regions.addresses = memory_acquire(8*sizeof(void*));
          memory_set(allocator->arena.regions.addresses, 0, 8*sizeof(void*));

          previous_allocator_capacity = allocator->arena.capacity;
          previous_allocator_data = allocator->arena.data;
          result = allocator_push(allocator, amount);

          must("double the arena regions capacity");
            verify(allocator->arena.regions.capacity == 16);
          must("create a region to store the previous arena data");
            verify(allocator->arena.regions.count == 9);
            verify(allocator->arena.regions.addresses[8] == previous_allocator_data);
          must("double the arena capacity");
            verify(allocator->arena.capacity == 2*previous_allocator_capacity);
          must("increase the arena position");
            verify(allocator->arena.position == amount);
          must("return a valid memory address");
            verify(result >= allocator->arena.data);
            verify(result <= allocator->arena.data + allocator->arena.capacity);

          success();
            allocator_release(allocator);
        } end();
      } end();

      when("the amount is greater than two times the current arena capacity") {
        amount = 80;

        when("the arena has no regions") {
          apply(preconditions);
          apply(previous_data_condition);
          allocator->arena.regions.addresses = nullptr;
          allocator->arena.regions.count = 0;

          previous_allocator_data = allocator->arena.data;
          result = allocator_push(allocator, amount);

          must("create a region to store the previous arena data");
            verify(allocator->arena.regions.count == 1);
            verify(allocator->arena.regions.addresses != nullptr);
            verify(allocator->arena.regions.addresses[0] == previous_allocator_data);
          must("increase the arena capacity to the next power of two of the amount");
            verify(allocator->arena.capacity == next_pow2(amount));
          must("increase the arena position");
            verify(allocator->arena.position == amount);
          must("return a valid memory address");
            verify(result >= allocator->arena.data);
            verify(result <= allocator->arena.data + allocator->arena.capacity);

          success();
            allocator_release(allocator);
        } end();

        when("the arena has one or more region, less than the regions capacity") {
          apply(preconditions);
          apply(previous_data_condition);
          allocator->arena.regions.count = 4;
          allocator->arena.regions.capacity = 8;
          allocator->arena.regions.addresses = memory_acquire(8*sizeof(void*));
          memory_set(allocator->arena.regions.addresses, 0, 8*sizeof(void*));

          previous_allocator_data = allocator->arena.data;
          result = allocator_push(allocator, amount);

          must("create a region to store the previous arena data");
            verify(allocator->arena.regions.count == 5);
            verify(allocator->arena.regions.addresses[4] == previous_allocator_data);
          must("increase the arena capacity to the next power of two of the amount");
            verify(allocator->arena.capacity == next_pow2(amount));
          must("increase the arena position");
            verify(allocator->arena.position == amount);
          must("return a valid memory address");
            verify(result >= allocator->arena.data);
            verify(result <= allocator->arena.data + allocator->arena.capacity);

          success();
            allocator_release(allocator);
        } end();

        when("the arena has one or more region, equal to the regions capacity") {
          apply(preconditions);
          apply(previous_data_condition);
          allocator->arena.regions.count = 8;
          allocator->arena.regions.capacity = 8;
          allocator->arena.regions.addresses = memory_acquire(8*sizeof(void*));
          memory_set(allocator->arena.regions.addresses, 0, 8*sizeof(void*));

          previous_allocator_data = allocator->arena.data;
          result = allocator_push(allocator, amount);

          must("double the arena regions capacity");
            verify(allocator->arena.regions.capacity == 16);
          must("create a region to store the previous arena data");
            verify(allocator->arena.regions.count == 9);
            verify(allocator->arena.regions.addresses[8] == previous_allocator_data);
          must("increase the arena capacity to the next power of two of the amount");
            verify(allocator->arena.capacity == next_pow2(amount));
          must("increase the arena position");
            verify(allocator->arena.position == amount);
          must("return a valid memory address");
            verify(result >= allocator->arena.data);
            verify(result <= allocator->arena.data + allocator->arena.capacity);

          success();
            allocator_release(allocator);
        } end();
      } end();

    } end();
  } end();
}
