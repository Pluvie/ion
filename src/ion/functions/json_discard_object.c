static inline bool json_discard_object_direct (
    struct io_direct* io
)
{
  #define JSON_DISCARD
  #include "../procedures/json_parse_object.c"
  #undef JSON_DISCARD

parse_success:
  return true;

parse_error:
  return false;
}



static inline bool json_discard_object_buffered (
    struct io_buffered* io
)
{
  #define JSON_DISCARD
  #include "../procedures/json_parse_object.c"
  #undef JSON_DISCARD

parse_success:
  return true;

parse_error:
  return false;
}
