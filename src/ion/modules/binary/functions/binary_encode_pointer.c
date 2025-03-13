static inline void binary_encode_pointer (
    struct reflection* rfx,
    struct io* io
)
{
  struct reflection* element_rfx = rfx->element;
  u64 element_size = element_rfx->size;

  void* pointer_address = *(void**) rfx->target;
  if (pointer_address == NULL)
    goto encode_null;

  /* Special case: a POINTER of type CHAR is intended to be a nul-terminated string. */
  if (element_rfx->type == CHAR)
    goto encode_string;
  else
    goto encode_pointer;

encode_string:
  u64 string_max_size = rfx->size_limits.min;
  u64 string_size = strlen(pointer_address) + 1;

  if (string_max_size > 0 && string_size > string_max_size) {
    fail("pointer required maximum string size of %li but found %li",
      string_max_size, element_rfx->size);
    return error_add_reflection_path(rfx);
  }

  io_write(io, &string_size, sizeof(u64));
  if (error.occurred)
    return error_add_reflection_path(rfx);

  io_write(io, pointer_address, string_size);
  if (error.occurred)
    return error_add_reflection_path(rfx);

  return;

encode_pointer:
  io_write(io, &element_size, sizeof(u64));
  if (error.occurred)
    return error_add_reflection_path(rfx);

  element_rfx->target = pointer_address;
  binary_encode(element_rfx, io);
  if (error.occurred)
    return;

  return;

encode_null:
  io_write(io, &(u64) { 0 }, sizeof(u64));
  if (error.occurred)
    return error_add_reflection_path(rfx);
}
