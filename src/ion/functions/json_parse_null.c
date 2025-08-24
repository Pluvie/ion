static inline int json_parse_null (
    struct io* io
)
{
  slice peek = io_peek(io, lengthof("null"));
  if (unlikely(failure.occurred))
    return -1;

  if (streq(peek, "null"))
    return lengthof("null");

  return 0;
}
