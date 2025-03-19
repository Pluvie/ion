static inline void binary_encode_pointer (
    void* obj,
    struct io* io,
    struct reflection* rfx
)
{
  struct reflection* element_rfx = rfx->element;
  element_rfx->parent = rfx;

  u64 element_size = element_rfx->size;
  void* element_obj = *(void**) obj;

  if (element_obj == NULL)
    goto encode_null;

  /* Special case: a POINTER of type CHAR is intended to be a nul-terminated string. */
  if (element_rfx->type == CHAR)
    goto encode_string;
  else
    goto encode_pointer;

encode_string:
  void* string_content = element_obj;
  u64 string_max_length = rfx->size_limits.max;
  u64 string_length = strlen(string_content) + 1;

  if (string_max_length > 0 && string_length > string_max_length) {
    fail("pointer required maximum string size of %li but found %li",
      string_max_length, string_length);
    return error_add_reflection_path(rfx);
  }

  io_write(io, &string_length, sizeof(u64));
  if (error.occurred)
    return error_add_reflection_path(rfx);

  io_write(io, string_content, string_length);
  if (error.occurred)
    return error_add_reflection_path(rfx);

  return;

encode_pointer:
  io_write(io, &element_size, sizeof(u64));
  if (error.occurred)
    return error_add_reflection_path(rfx);

  binary_encode(element_obj, io, element_rfx);
  if (error.occurred)
    return;

  return;

encode_null:
  io_write(io, &(addr) { 0 }, sizeof(addr));
  if (error.occurred)
    return error_add_reflection_path(rfx);
}
