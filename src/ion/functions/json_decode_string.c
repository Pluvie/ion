static inline void json_decode_string_direct (
    struct io_direct* io,
    struct reflection* rfx,
    void* target
)
{
  string* result = (string*) target;
  #include "../procedures/json_parse_string.c"

parse_success:
  if (reflection_validate(rfx, target))
    return;

  goto add_failure_info;

parse_failure:
  fail("expected a string");

add_failure_info:
  failure_add_io_info(io);
  failure_add_reflection_info(rfx);
  return;
}



static inline void json_decode_string_buffered (
    struct io_buffered* io,
    struct reflection* rfx,
    void* target
)
{
//  string* result = (string*) target;
//  #include "../procedures/json_parse_string.c"
//
//parse_success:
//  /* Add reflection validation. */
//  string copy = { 0 };
//  copy.pointer = memory_alloc(io->allocator, result->length);
//  byte_copy(copy.pointer, result->pointer, result->length);
//  byte_copy(target, &copy, sizeof(string));
//  return;
//
//parse_failure:
//  fail("expected a string");
//  return;
}
