#include "buffer_pop.h"

spec( buffer_pop ) {
  argument(struct buffer* buffer);
  argument(uint amount);
  returns(void* result);

  precondition("a valid, previously initialized buffer");
  #define preconditions \
    struct buffer initialized_buffer = buffer_init(64); \
    buffer = &initialized_buffer;

  when("the amount is not greater than the buffer position") {
    apply(preconditions);
    amount = 24;
    buffer->position = 32;
    result = buffer_pop(buffer, amount);

    must("decrease the buffer position by the given amount");
      verify(buffer->position == 32 - 24);
    must("return a pointer to the buffer data offset");
      verify(result == buffer->data + buffer->position);

    success();
  } end();

  when("the amount is greater than the buffer position") {
    apply(preconditions);
    amount = 48;
    buffer->position = 32;
    result = buffer_pop(buffer, amount);

    must("set the buffer position to 0");
      verify(buffer->position == 0);
    must("return a pointer to the buffer data");
      verify(result == buffer->data);

    success();
  } end();
}
