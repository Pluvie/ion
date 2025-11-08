#include "buffer_release.h"

spec( buffer_release ) {
  argument(struct buffer* buffer);

  precondition("a valid, previously initialized buffer");
  #define preconditions \
    memory_set(&initialized_buffer, 0, sizeof(initialized_buffer)); \
    initialized_buffer.data = (byte*) 0x01; \
    buffer = &initialized_buffer;

  apply(preconditions);
  buffer_release(buffer);

  must("release the buffer data");
    verify(sim.released[0] == (void*) 0x01);
  must("zero out the buffer struct");
    verify(memory_equal(buffer, &released_buffer, sizeof(*buffer)));

  success();
}
