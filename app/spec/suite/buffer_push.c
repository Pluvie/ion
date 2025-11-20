#include "buffer_push.h"

spec( buffer_push ) {
  argument(struct buffer* allocator);
  argument(uint amount);
  returns(byte* result);

  precondition("a valid, previously initialized buffer allocator");
  #define preconditions \
    initialized_allocator = buffer_create(32); \
    allocator = &initialized_allocator;

  when("the line has no previous data") {
    when("the amount is not greater than the line capacity") {
      amount = 16;
      apply(preconditions);
      result = buffer_push(allocator, amount);

      must("increase the line position by the requested amount");
        verify(allocator->position == amount);
      must("return a valid memory address");
        verify(result >= allocator->data);
        verify(result <= allocator->data + allocator->capacity);

      success();
        buffer_destroy(allocator);
    } end();

    when("the amount is greater than the line capacity") {
      amount = 50;
      apply(preconditions);
      result = buffer_push(allocator, amount);

      must("increase the line capacity to the amount");
        verify(allocator->capacity == amount);
      must("increase the line position");
        verify(allocator->position == amount);
      must("return a valid memory address");
        verify(result >= allocator->data);
        verify(result <= allocator->data + allocator->capacity);

      success();
        buffer_destroy(allocator);
    } end();
  } end();

  when("the line has previous data") {
    #define previous_data_condition \
      buffer_push(allocator, 16);
    int previous_buffer_capacity;
    int previous_buffer_position;

    when("the amount is not greater than the remaining line space") {
      amount = 8;
      apply(preconditions);
      apply(previous_data_condition);

      previous_buffer_position = allocator->position;
      result = buffer_push(allocator, amount);

      must("increase the line position by the requested amount");
        verify(allocator->position == previous_buffer_position + amount);
      must("return a valid memory address");
        verify(result >= allocator->data);
        verify(result <= allocator->data + allocator->capacity);

      success();
        buffer_destroy(allocator);
    } end();

    when("the amount is greater than the line remaining space") {
      when("the amount is not greater than two times the current line capacity") {
        amount = 24;

        apply(preconditions);
        apply(previous_data_condition);

        previous_buffer_capacity = allocator->capacity;
        previous_buffer_position = allocator->position;
        result = buffer_push(allocator, amount);

        must("double the line capacity");
          verify(allocator->capacity == 2*previous_buffer_capacity);
        must("increase the line position");
          verify(allocator->position == previous_buffer_position + amount);
        must("return a valid memory address");
          verify(result >= allocator->data);
          verify(result <= allocator->data + allocator->capacity);

        success();
          buffer_destroy(allocator);
      } end();

      when("the amount is greater than two times the current line capacity") {
        amount = 80;

        apply(preconditions);
        apply(previous_data_condition);

        previous_buffer_position = allocator->position;
        result = buffer_push(allocator, amount);

        must("increase the line capacity to the amount plus the position");
          verify(allocator->capacity == amount + previous_buffer_position);
        must("increase the line position");
          verify(allocator->position == previous_buffer_position + amount);
        must("return a valid memory address");
          verify(result >= allocator->data);
          verify(result <= allocator->data + allocator->capacity);

        success();
          buffer_destroy(allocator);
      } end();

    } end();
  } end();
}
