static inline void binary_decode_string (
    struct io* io,
    struct reflection* rfx
)
{
check_string_size:
  u64 string_max_length = rfx->size_limits.min;
  u64* string_length = io_read(io, sizeof(u64));
  if (error.occurred)
    return error_add_reflection_path(rfx);

  if (string_max_length > 0 && *string_length > string_max_length) {
    fail("string required maximum string length of %li but found %li",
      string_max_length, *string_length);
    return error_add_reflection_path(rfx);
  }

allocate_string:
  struct string string = { 0 };
  string.length = *string_length;
  string.content = memory_alloc(rfx->allocator, string.length);
  
  char* string_content = io_read(io, string.length);
  if (error.occurred)
    return;

  memcpy(string.content, string_content, string.length);
  goto validate_string;

validate_string:
  reflection_validate(rfx, &string);
  if (error.occurred)
    return error_add_reflection_path(rfx);

copy_string:
  memcpy(rfx->target, &string, sizeof(struct string));
}
