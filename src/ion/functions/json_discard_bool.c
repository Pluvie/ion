static inline void json_discard_bool_direct (
    struct io_direct* io
)
{
  #define JSON_DISCARD
  #include "../procedures/json_parse_bool.c"
  #undef JSON_DISCARD

parse_success:
  return;

parse_error:
  fail("json parse error: discard bool");
  return;
}



static inline void json_discard_bool_buffered (
    struct io_buffered* io
)
{
  #define JSON_DISCARD
  #include "../procedures/json_parse_bool.c"
  #undef JSON_DISCARD

parse_success:
  return;

parse_error:
  fail("json parse error: discard bool");
  return;
}
