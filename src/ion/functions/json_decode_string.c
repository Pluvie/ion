static inline void json_decode_string_direct (
    struct io_direct* io,
    void* target
)
{
  string* result = (string*) target;
  #include "../procedures/json_parse_string.c"

parse_success:
  /* Add reflection validation. */
  return;

parse_error:
  fail("expected a string");
  return;
}



static inline void json_decode_string_buffered (
    struct io_buffered* io,
    void* target
)
{
  string* result = (string*) target;
  #include "../procedures/json_parse_string.c"

parse_success:
  /* Add reflection validation. */
  string copy = { 0 };
  copy.pointer = memory_alloc(io->allocator, result->length);
  byte_copy(copy.pointer, result->pointer, result->length);
  byte_copy(target, &copy, sizeof(string));
  return;

parse_error:
  fail("expected a string");
  return;
}
