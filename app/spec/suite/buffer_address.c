#include "buffer_address.h"

spec( buffer_address ) {
  argument(struct buffer* buffer);
  returns(void* result);

  precondition("a valid, previously initialized buffer");
  #define preconditions \
    initialized_buffer = buffer_init(64); \
    initialized_buffer.position = 32; \
    buffer = &initialized_buffer;

  apply(preconditions);
  result = buffer_address(buffer);

  must("return a pointer to the buffer data at its current position");
    verify(result == ((byte*) buffer->data) + buffer->position);

  success();
  end();
}
