#include "buffer_push.h"

spec( buffer_push ) {
  argument(struct buffer* buffer);
  argument(uint amount);
  returns(byte* result);

  precondition("a valid, previously initialized buffer");
  #define preconditions \
    initialized_buffer = buffer_init(32); \
    buffer = &initialized_buffer;

  when("the line has no previous data") {
    when("the amount is not greater than the line capacity") {
      amount = 16;
      apply(preconditions);
      result = buffer_push(buffer, amount);

      must("increase the line position by the requested amount");
        verify(buffer->position == amount);
      must("return a valid memory address");
        verify(result >= buffer->data);
        verify(result <= buffer->data + buffer->capacity);

      success();
        buffer_release(buffer);
    } end();

    when("the amount is greater than the line capacity") {
      amount = 50;
      apply(preconditions);
      result = buffer_push(buffer, amount);

      must("increase the line capacity to the amount");
        verify(buffer->capacity == amount);
      must("increase the line position");
        verify(buffer->position == amount);
      must("return a valid memory address");
        verify(result >= buffer->data);
        verify(result <= buffer->data + buffer->capacity);

      success();
        buffer_release(buffer);
    } end();
  } end();

  when("the line has previous data") {
    #define previous_data_condition \
      buffer_push(buffer, 16);
    int previous_buffer_capacity;
    int previous_buffer_position;

    when("the amount is not greater than the remaining line space") {
      amount = 8;
      apply(preconditions);
      apply(previous_data_condition);

      previous_buffer_position = buffer->position;
      result = buffer_push(buffer, amount);

      must("increase the line position by the requested amount");
        verify(buffer->position == previous_buffer_position + amount);
      must("return a valid memory address");
        verify(result >= buffer->data);
        verify(result <= buffer->data + buffer->capacity);

      success();
        buffer_release(buffer);
    } end();

    when("the amount is greater than the line remaining space") {
      when("the amount is not greater than two times the current line capacity") {
        amount = 24;

        apply(preconditions);
        apply(previous_data_condition);

        previous_buffer_capacity = buffer->capacity;
        previous_buffer_position = buffer->position;
        result = buffer_push(buffer, amount);

        must("double the line capacity");
          verify(buffer->capacity == 2*previous_buffer_capacity);
        must("increase the line position");
          verify(buffer->position == previous_buffer_position + amount);
        must("return a valid memory address");
          verify(result >= buffer->data);
          verify(result <= buffer->data + buffer->capacity);

        success();
          buffer_release(buffer);
      } end();

      when("the amount is greater than two times the current line capacity") {
        amount = 80;

        apply(preconditions);
        apply(previous_data_condition);

        previous_buffer_position = buffer->position;
        result = buffer_push(buffer, amount);

        must("increase the line capacity to the amount plus the position");
          verify(buffer->capacity == amount + previous_buffer_position);
        must("increase the line position");
          verify(buffer->position == previous_buffer_position + amount);
        must("return a valid memory address");
          verify(result >= buffer->data);
          verify(result <= buffer->data + buffer->capacity);

        success();
          buffer_release(buffer);
      } end();

    } end();
  } end();
}
