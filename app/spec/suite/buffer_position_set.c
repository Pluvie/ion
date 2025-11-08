#include "buffer_position_set.h"

spec( buffer_position_set ) {
  argument(struct buffer* buffer);
  argument(uint position);

  precondition("a valid, previously initialized buffer");
  #define preconditions \
    initialized_buffer = buffer_init(64); \
    buffer = &initialized_buffer;

  apply(preconditions);
  position = 32;
  buffer_position_set(buffer, position);

  must("set the current buffer position");
    verify(buffer->position == position);

  success();
  end();
}
