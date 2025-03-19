static inline void json_decode_string (
    void* obj,
    struct io* io,
    struct reflection* rfx,
    struct memory* allocator
)
{
check_string_size:
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

allocate_string:
  struct string string = { 0 };
  char* string_content = io_read(io, string_length);
  if (error.occurred)
    return;

  /* Removes the surrounding '"'. */
  string.length = string_length - 2;
  string.content = memory_alloc(allocator, string.length + 1);
  memcpy(string.content, string_content + 1, string.length);
  string.content[string.length] = '\0';

  goto validate_string;

validate_string:
  reflection_validate(rfx, &string);
  if (error.occurred)
    return error_add_reflection_path(rfx);

copy_string:
  memcpy(obj, &string, sizeof(struct string));
}
