static inline void json_encode_string (
    void* obj,
    struct io* io,
    struct reflection* rfx
)
{
  io_write(io, "\"", 1);
  if (unlikely(failure.occurred))
    return;

  struct string* string = obj;
  io_write(io, string->content, string->length);
  if (unlikely(failure.occurred))
    return;

  io_write(io, "\"", 1);
  if (unlikely(failure.occurred))
    return;
}
