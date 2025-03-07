static inline void binary_encode_string (
    struct reflection* rfx,
    struct io* io
)
{
  struct string* string = (struct string*) rfx->target;

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
  io_write(io, string->content, string->length);
  if (error.occurred)
    return error_add_reflection_path(rfx);
}
