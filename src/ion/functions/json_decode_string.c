void json_decode_string (
    void* obj,
    struct io* io,
    struct reflection* rfx,
    struct memory* allocator
)
{
  int string_length = json_parse_string(io);
  if (unlikely(failure.occurred))
    return;

  if (string_length < 2) {
    fail("expected a string");
    failure_add_reflection_info(rfx);
    failure_add_io_info(io);
    return;
  }

  slice result = io_read(io, string_length);
  if (unlikely(failure.occurred))
    return;

  /* Removes the surrounding '"'. */
  string value = { result.data + 1, result.length - 2 };

  int string_max_length = rfx->size_limits.max;
  if (string_max_length > 0 && value.length > string_max_length) {
    fail("string required maximum string size of %li but found %li",
      string_max_length, value.length);
    failure_add_reflection_info(rfx);
    failure_add_io_info(io);
    return;
  }
  int string_min_length = rfx->size_limits.min;
  if (string_min_length > 0 && value.length < string_min_length) {
    fail("string required minimum string length of %li but found %li",
      string_min_length, value.length);
    failure_add_reflection_info(rfx);
    failure_add_io_info(io);
    return;
  }

  reflection_validate(rfx, &value);
  if (unlikely(failure.occurred))
    return failure_add_reflection_info(rfx);

  if (io->channel == IO_MEMORY && io->buffer.enabled == false) {
    byte_copy(obj, &value, sizeof(string));
  } else {
    string copy = { 0 };
    copy.content = memory_alloc(allocator, value.length);
    byte_copy(copy.content, value.content, value.length);
    byte_copy(obj, &copy, sizeof(string));
  }
}
