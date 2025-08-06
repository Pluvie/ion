static inline void json_decode_string (
    void* obj,
    struct io* io,
    struct reflection* rfx,
    struct memory* allocator
)
{
  int string_length = json_parse_string(io);
  if (error.occurred)
    return;

  if (string_length < 2) {
    fail("expected a string");
    reflection_error_extract(rfx);
    io_error_extract(io);
    return;
  }

  slice result = io_read(io, string_length);
  if (error.occurred)
    return;

  /* Removes the surrounding '"'. */
  string value = { result.data + 1, result.length - 2 };

  int string_max_length = rfx->size_limits.max;
  if (string_max_length > 0 && value.length > string_max_length) {
    fail("string required maximum string size of %li but found %li",
      string_max_length, value.length);
    reflection_error_extract(rfx);
    io_error_extract(io);
    return;
  }
  int string_min_length = rfx->size_limits.min;
  if (string_min_length > 0 && value.length < string_min_length) {
    fail("string required minimum string length of %li but found %li",
      string_min_length, value.length);
    reflection_error_extract(rfx);
    io_error_extract(io);
    return;
  }

  reflection_validate(rfx, &value);
  if (error.occurred)
    return reflection_error_extract(rfx);

  if (io->channel == IO_MEMORY && io->buffer.enabled == false) {
    memcpy(obj, &value, sizeof(string));
  } else {
    string copy = { 0 };
    copy.content = memory_alloc(allocator, value.length);
    memcpy(copy.content, value.content, value.length);
    memcpy(obj, &copy, sizeof(string));
  }
}
