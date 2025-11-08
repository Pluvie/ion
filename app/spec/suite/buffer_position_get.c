#include "buffer_position_get.h"

spec( buffer_position_get ) {
  argument(struct buffer* buffer);
  returns(uint result);

  precondition("a valid, previously initialized buffer");
  #define preconditions \
    initialized_buffer = buffer_init(64); \
    initialized_buffer.position = 32; \
    buffer = &initialized_buffer;

  apply(preconditions);
  result = buffer_position_get(buffer);

  must("return the current buffer position");
    verify(result == buffer->position);

  success();
  end();
}
