static inline void binary_encode_pointer (
    struct reflection* rfx,
    struct io* io
)
{
  struct reflection* element_rfx = rfx->element;
  void* pointer_address = *(void**) rfx->target;

  /* Special case: a POINTER size of type CHAR must be explicitly sent, as its
   * length is not fixed and not known a priori. */
  if (element_rfx->type == CHAR)
    goto check_string_size;
  else
    goto encode_pointer;

check_string_size:
  u64 string_max_size = rfx->size_limits.min;
  u64 string_size = strlen(pointer_address) + 1;

  if (string_max_size > 0 && string_size > string_max_size) {
    fail("pointer required maximum string size of %li but found %li",
      string_max_size, element_rfx->size);
    return error_add_reflection_path(rfx);
  }

encode_length:
  io_write(io, &string_size, sizeof(string_size));
  if (error.occurred)
    return error_add_reflection_path(rfx);

encode_string:
  io_write(io, pointer_address, string_size);
  if (error.occurred)
    return error_add_reflection_path(rfx);

  return;

encode_pointer:
  element_rfx->target = pointer_address;
  binary_encode(element_rfx, io);
  if (error.occurred)
    return;
}
