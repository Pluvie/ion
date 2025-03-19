static inline void json_decode_pointer (
    void* obj,
    struct io* io,
    struct reflection* rfx,
    struct memory* allocator
)
{
  struct reflection* element_rfx = rfx->element;
  element_rfx->parent = rfx;

  u64 pointer_size = element_rfx->size;
  void* pointer_data = NULL;

  /* Special case: a POINTER of type CHAR is intended to be a nul-terminated string. */
  if (element_rfx->type == CHAR)
    goto allocate_string;
  else
    goto allocate_pointer;

allocate_string:
  u64 string_max_length = rfx->size_limits.max;
  u64 string_length = json_parse_string(io);
  if (error.occurred)
    return;

  if (string_length == 0) {
    fail("expected a string");
    error_add_io_extraction(io);
    error_add_reflection_path(rfx);
    return;
  }

  /* In checking the string size, does not consider the surrounding '"'. */
  if (string_max_length > 0 && (string_length - 2) > string_max_length) {
    fail("pointer required maximum string size of %li but found %li",
      string_max_length, string_length);
    error_add_io_extraction(io);
    error_add_reflection_path(rfx);
    return;
  }

  char* string_content = io_read(io, string_length);
  if (error.occurred)
    return;

  /* Removes the surrounding '"'. */
  string_length = string_length - 2;
  pointer_data = memory_alloc(allocator, string_length + 1);
  memcpy(pointer_data, string_content + 1, string_length);
  ((char*) pointer_data)[string_length] = '\0';

  goto validate_pointer;

allocate_pointer:
  pointer_data = memory_alloc(allocator, pointer_size);

  json_decode(pointer_data, io, element_rfx, allocator);
  if (error.occurred)
    return;

validate_pointer:
  reflection_validate(rfx, pointer_data);
  if (error.occurred)
    return error_add_reflection_path(rfx);

copy_pointer:
  addr pointer_address = (addr) pointer_data;
  memcpy(obj, &pointer_address, sizeof(addr));
}
