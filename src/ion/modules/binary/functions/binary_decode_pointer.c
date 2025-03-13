static inline void binary_decode_pointer (
    struct io* io,
    struct reflection* rfx
)
{
  struct reflection* element_rfx = rfx->element;
  u64 element_size = element_rfx->size;
  void* pointer_data = NULL;

read_length:
  u64* pointer_size = io_read(io, sizeof(u64));
  if (error.occurred)
    return error_add_reflection_path(rfx);

  if (*pointer_size == 0)
    goto allocate_null;

  /* Special case: a POINTER of type CHAR is intended to be a nul-terminated string. */
  if (element_rfx->type == CHAR)
    goto allocate_string;
  else
    goto allocate_pointer;

allocate_string:
  u64 string_max_size = rfx->size_limits.max;

  if (string_max_size > 0 && *pointer_size > string_max_size) {
    fail("pointer required maximum string size of %li but found %li",
      string_max_size, *pointer_size);
    return error_add_reflection_path(rfx);
  }

  pointer_data = memory_alloc(rfx->allocator, *pointer_size);

  char* string = io_read(io, *pointer_size);
  if (error.occurred)
    return;

  memcpy(pointer_data, string, *pointer_size);
  goto validate_pointer;

allocate_pointer:
  if (*pointer_size != element_size) {
    fail("pointer required element size of %li but found %li",
      element_size, *pointer_size);
    return error_add_reflection_path(rfx);
  }

  pointer_data = memory_alloc(rfx->allocator, element_size);

  element_rfx->target = pointer_data;
  binary_decode(io, element_rfx);
  if (error.occurred)
    return;

  goto validate_pointer;

allocate_null:
  rfx->target = NULL;
  return;

validate_pointer:
  reflection_validate(rfx, pointer_data);
  if (error.occurred)
    return error_add_reflection_path(rfx);

copy_pointer:
  addr pointer_address = (addr) pointer_data;
  memcpy(rfx->target, &pointer_address, sizeof(addr));
}
