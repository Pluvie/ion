#include "buffer_address_at.h"

spec( buffer_address_at ) {
  argument(struct buffer* buffer);
  argument(uint position);
  returns(void* result);

  precondition("a valid, previously initialized buffer");
  #define preconditions \
    initialized_buffer = buffer_init(64); \
    buffer = &initialized_buffer;

  apply(preconditions);
  position = 32;
  result = buffer_address_at(buffer, position);

  must("return a pointer to the buffer data at the requested position");
    verify(result == ((byte*) buffer->data) + position);

  success();
  end();
}
