#include "allocator_push.h"

spec( allocator_push ) {
  argument(struct allocator* allocator);
  argument(uint amount);
  returns(byte* result);

  precondition("a valid, previously initialized allocator");
  #define preconditions \
    initialized_allocator = allocator_init(32); \
    allocator = &initialized_allocator;

  when("the allocator has no previous data") {
    when("the amount is not greater than the allocator capacity") {
      amount = 16;
      apply(preconditions);
      result = allocator_push(allocator, amount);

      must("increase the allocator position by the requested amount");
        verify(allocator->position == amount);
      must("return a valid memory address");
        verify(result >= allocator->data);
        verify(result <= allocator->data + allocator->capacity);

      success();
        allocator_release(allocator);
    } end();

    when("the amount is greater than the allocator capacity") {
      amount = 50;
      apply(preconditions);
      result = allocator_push(allocator, amount);

      must("increase the allocator capacity to the next power of two of the amount");
        verify(allocator->capacity == next_pow2(amount));
      must("increase the allocator position");
        verify(allocator->position == amount);
      must("return a valid memory address");
        verify(result >= allocator->data);
        verify(result <= allocator->data + allocator->capacity);

      success();
        allocator_release(allocator);
    } end();
  } end();

  when("the allocator has previous data") {
    #define previous_data_condition \
      allocator_push(allocator, 16);
    byte* previous_allocator_data;
    int previous_allocator_capacity;
    int previous_allocator_position;

    when("the amount is not greater than the remaining allocator space") {
      amount = 8;
      apply(preconditions);
      apply(previous_data_condition);

      previous_allocator_position = allocator->position;
      result = allocator_push(allocator, amount);

      must("increase the allocator position by the requested amount");
        verify(allocator->position == previous_allocator_position + amount);
      must("return a valid memory address");
        verify(result >= allocator->data);
        verify(result <= allocator->data + allocator->capacity);

      success();
        allocator_release(allocator);
    } end();

    when("the amount is greater than the allocator remaining space") {
      when("the amount is not greater than two times the current allocator capacity") {
        amount = 24;

        when("the allocator has no regions") {
          apply(preconditions);
          apply(previous_data_condition);
          allocator->regions.addresses = nullptr;
          allocator->regions.count = 0;

          previous_allocator_capacity = allocator->capacity;
          previous_allocator_data = allocator->data;
          result = allocator_push(allocator, amount);

          must("create a region to store the previous allocator data");
            verify(allocator->regions.count == 1);
            verify(allocator->regions.addresses != nullptr);
            verify(allocator->regions.addresses[0] == previous_allocator_data);
          must("double the allocator capacity");
            verify(allocator->capacity == 2*previous_allocator_capacity);
          must("increase the allocator position");
            verify(allocator->position == amount);
          must("return a valid memory address");
            verify(result >= allocator->data);
            verify(result <= allocator->data + allocator->capacity);

          success();
            allocator_release(allocator);
        } end();

        when("the allocator has one or more region, less than the regions capacity") {
          apply(preconditions);
          apply(previous_data_condition);
          allocator->regions.count = 4;
          allocator->regions.capacity = 8;
          allocator->regions.addresses = memory_acquire(8*sizeof(void*));
          memory_set(allocator->regions.addresses, 0, 8*sizeof(void*));

          previous_allocator_capacity = allocator->capacity;
          previous_allocator_data = allocator->data;
          result = allocator_push(allocator, amount);

          must("create a region to store the previous allocator data");
            verify(allocator->regions.count == 5);
            verify(allocator->regions.addresses[4] == previous_allocator_data);
          must("double the allocator capacity");
            verify(allocator->capacity == 2*previous_allocator_capacity);
          must("increase the allocator position");
            verify(allocator->position == amount);
          must("return a valid memory address");
            verify(result >= allocator->data);
            verify(result <= allocator->data + allocator->capacity);

          success();
            allocator_release(allocator);
        } end();

        when("the allocator has one or more region, equal to the regions capacity") {
          apply(preconditions);
          apply(previous_data_condition);
          allocator->regions.count = 8;
          allocator->regions.capacity = 8;
          allocator->regions.addresses = memory_acquire(8*sizeof(void*));
          memory_set(allocator->regions.addresses, 0, 8*sizeof(void*));

          previous_allocator_capacity = allocator->capacity;
          previous_allocator_data = allocator->data;
          result = allocator_push(allocator, amount);

          must("double the allocator regions capacity");
            verify(allocator->regions.capacity == 16);
          must("create a region to store the previous allocator data");
            verify(allocator->regions.count == 9);
            verify(allocator->regions.addresses[8] == previous_allocator_data);
          must("double the allocator capacity");
            verify(allocator->capacity == 2*previous_allocator_capacity);
          must("increase the allocator position");
            verify(allocator->position == amount);
          must("return a valid memory address");
            verify(result >= allocator->data);
            verify(result <= allocator->data + allocator->capacity);

          success();
            allocator_release(allocator);
        } end();
      } end();

      when("the amount is greater than two times the current allocator capacity") {
        amount = 80;

        when("the allocator has no regions") {
          apply(preconditions);
          apply(previous_data_condition);
          allocator->regions.addresses = nullptr;
          allocator->regions.count = 0;

          previous_allocator_data = allocator->data;
          result = allocator_push(allocator, amount);

          must("create a region to store the previous allocator data");
            verify(allocator->regions.count == 1);
            verify(allocator->regions.addresses != nullptr);
            verify(allocator->regions.addresses[0] == previous_allocator_data);
          must("increase the allocator capacity to the next power of two of the amount");
            verify(allocator->capacity == next_pow2(amount));
          must("increase the allocator position");
            verify(allocator->position == amount);
          must("return a valid memory address");
            verify(result >= allocator->data);
            verify(result <= allocator->data + allocator->capacity);

          success();
            allocator_release(allocator);
        } end();

        when("the allocator has one or more region, less than the regions capacity") {
          apply(preconditions);
          apply(previous_data_condition);
          allocator->regions.count = 4;
          allocator->regions.capacity = 8;
          allocator->regions.addresses = memory_acquire(8*sizeof(void*));
          memory_set(allocator->regions.addresses, 0, 8*sizeof(void*));

          previous_allocator_data = allocator->data;
          result = allocator_push(allocator, amount);

          must("create a region to store the previous allocator data");
            verify(allocator->regions.count == 5);
            verify(allocator->regions.addresses[4] == previous_allocator_data);
          must("increase the allocator capacity to the next power of two of the amount");
            verify(allocator->capacity == next_pow2(amount));
          must("increase the allocator position");
            verify(allocator->position == amount);
          must("return a valid memory address");
            verify(result >= allocator->data);
            verify(result <= allocator->data + allocator->capacity);

          success();
            allocator_release(allocator);
        } end();

        when("the allocator has one or more region, equal to the regions capacity") {
          apply(preconditions);
          apply(previous_data_condition);
          allocator->regions.count = 8;
          allocator->regions.capacity = 8;
          allocator->regions.addresses = memory_acquire(8*sizeof(void*));
          memory_set(allocator->regions.addresses, 0, 8*sizeof(void*));

          previous_allocator_data = allocator->data;
          result = allocator_push(allocator, amount);

          must("double the allocator regions capacity");
            verify(allocator->regions.capacity == 16);
          must("create a region to store the previous allocator data");
            verify(allocator->regions.count == 9);
            verify(allocator->regions.addresses[8] == previous_allocator_data);
          must("increase the allocator capacity to the next power of two of the amount");
            verify(allocator->capacity == next_pow2(amount));
          must("increase the allocator position");
            verify(allocator->position == amount);
          must("return a valid memory address");
            verify(result >= allocator->data);
            verify(result <= allocator->data + allocator->capacity);

          success();
            allocator_release(allocator);
        } end();
      } end();

    } end();
  } end();
}
