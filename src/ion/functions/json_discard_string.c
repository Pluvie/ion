static inline void json_discard_string_direct (
    struct io_direct* io
)
{
  #define JSON_DISCARD
  #include "../procedures/json_parse_string.c"
  #undef JSON_DISCARD

parse_success:
  return;

parse_error:
  fail("json parse error: discard string");
  return;
}



static inline void json_discard_string_buffered (
    struct io_buffered* io
)
{
  #define JSON_DISCARD
  #include "../procedures/json_parse_string.c"
  #undef JSON_DISCARD

parse_success:
  return;

parse_error:
  fail("json parse error: discard string");
  return;
}
