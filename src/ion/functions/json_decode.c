void json_decode (
    struct io* io,
    void* target
)
{
  switch (io->type) {
  case IO_DIRECT:
    if (io->rfx != NULL)
      { json_decode_direct(io->direct, io->rfx, target); return; }
    else
      { json_discard_value(io->direct); return; }

  case IO_BUFFERED:
    if (io->rfx != NULL)
      { json_decode_buffered(io->buffered, io->rfx, target); return; }
    else
      { json_discard_value(io->buffered); return; }

  default:
    fail("json decode: unrecognized io type");
  }

  return;
}


static inline void json_decode_direct (
    struct io_direct* io,
    struct reflection* rfx,
    void* target
)
{
  json_decode_value(io, rfx, target);
}



static inline void json_decode_buffered (
    struct io_buffered* io,
    struct reflection* rfx,
    void* target
)
{
  json_decode_value(io, rfx, target);
}
