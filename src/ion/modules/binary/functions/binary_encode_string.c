static inline void binary_encode_string (
    void* obj,
    struct io* io,
    struct reflection* rfx
)
{
  struct string* string = (struct string*) obj;

check_string_size:
  u64 string_max_length = rfx->size_limits.max;

  if (string_max_length > 0 && string->length > string_max_length) {
    fail("string required maximum string length of %li but found %li",
      string_max_length, string->length);
    return error_add_reflection_path(rfx);
  }

encode_length:
  io_write(io, &(string->length), sizeof(string->length));
  if (error.occurred)
    return error_add_reflection_path(rfx);

encode_content:
  if (string->length == 0)
    return;

  io_write(io, string->content, string->length);
  if (error.occurred)
    return error_add_reflection_path(rfx);
}
