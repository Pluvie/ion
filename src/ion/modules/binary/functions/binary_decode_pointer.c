static inline void binary_decode_pointer (
    struct io* io,
    struct reflection* rfx
)
{
  struct reflection* element_rfx = rfx->element;
  u64 element_size = element_rfx->size;

  /* Special case: a POINTER size of type CHAR must be explicitly sent, as its
   * length is not fixed and not known a priori. */
  if (element_rfx->type == CHAR)
    goto check_string_size;
  else
    goto allocate_pointer;

check_string_size:
  u64 string_max_size = rfx->size_limits.max;
  u64* string_size = io_read(io, sizeof(u64));
  if (error.occurred)
    return error_add_reflection_path(rfx);

  if (string_max_size > 0 && *string_size > string_max_size) {
    fail("pointer required maximum string size of %li but found %li",
      string_max_size, *string_size);
    return error_add_reflection_path(rfx);
  }

  element_size = *string_size;

allocate_pointer:
  void* pointer_data = memory_alloc(rfx->allocator, element_size);

  if (element_rfx->type == CHAR)
    goto pointer_type_char;
  else
    goto pointer_type_other;

pointer_type_char:
  /* Special case: a POINTER of type CHAR is intended to be a nul-terminated string. */
  char* string = io_read(io, element_size);
  if (error.occurred)
    return;

  memcpy(pointer_data, string, element_size);
  goto validate_pointer;

pointer_type_other:
  element_rfx->target = pointer_data;
  binary_decode(io, element_rfx);
  if (error.occurred)
    return;

validate_pointer:
  reflection_validate(rfx, pointer_data);
  if (error.occurred)
    return error_add_reflection_path(rfx);

copy_pointer:
  addr pointer_address = (addr) pointer_data;
  memcpy(rfx->target, &pointer_address, sizeof(addr));
}
