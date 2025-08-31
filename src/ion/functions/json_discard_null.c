static inline void json_discard_null_direct (
    struct io_direct* io
)
{
  #define JSON_DISCARD
  #include "../procedures/json_parse_null.c"
  #undef JSON_DISCARD

parse_success:
  return;

parse_error:
  fail("json parse error: discard null");
  return;
}



static inline void json_discard_null_buffered (
    struct io_buffered* io
)
{
  #define JSON_DISCARD
  #include "../procedures/json_parse_null.c"
  #undef JSON_DISCARD

parse_success:
  return;

parse_error:
  fail("json parse error: discard null");
  return;
}
