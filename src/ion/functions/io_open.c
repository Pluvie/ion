static inline struct io io_open_string (
    string* source
)
{
  struct io result = {
    .direct = {
      .data = source,
      .cursor = source->pointer,
      .end = source->pointer + source->length,
    },
    .type = IO_DIRECT,
  };
  return result;
}
