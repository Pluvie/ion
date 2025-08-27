int json_parse_null (
    struct io* io
)
{
  io_peek(io, 4);
  if (unlikely(failure.occurred))
    return -1;

  if (cmp<string>(io->result, s("null")) == 0) {
    io_read(io, 4);
    return 4;
  }

  return -1;
}
