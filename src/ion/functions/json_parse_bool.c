static inline int json_parse_bool (
    struct io* io
)
{
  io_peek(io, 5);
  if (unlikely(failure.occurred))
    return -1;

  if (cmp<string>(io->result, s("true")) == 0) {
    io_read(io, 4);
    return 4;
  }

  if (cmp<string>(io->result, s("false")) == 0) {
    io_read(io, 5);
    return 5;
  }

  return -1;
}
