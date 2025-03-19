static inline void json_encode_string (
    void* obj,
    struct io* io,
    struct reflection* rfx
)
{
  io_write(io, "\"", 1);
  if (error.occurred)
    return;

  struct string* string = obj;
  io_write(io, string->content, string->length);
  if (error.occurred)
    return;

  io_write(io, "\"", 1);
  if (error.occurred)
    return;
}
