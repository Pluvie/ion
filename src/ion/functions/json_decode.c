void json_decode (
    struct io* io,
    void* target
)
{
  switch (io->type) {
  case IO_DIRECT:
    if (io->rfx != NULL)
      return json_decode_direct(&(io->direct), target);
    else
      return json_discard_value_direct(&(io->direct));

  case IO_BUFFERED:
    if (io->rfx != NULL)
      return json_decode_buffered(&(io->buffered), target);
    else
      return json_discard_value_buffered(&(io->direct));

  default:
    fail("json decode: unrecognized io type");
  }
}


static inline void json_decode_direct (
    struct io_direct* io,
    void* target
)
#include "../procedures/json_parse.c"



static inline void json_decode_buffered (
    struct io_buffered* io,
    void* target
)
#include "../procedures/json_parse.c"
