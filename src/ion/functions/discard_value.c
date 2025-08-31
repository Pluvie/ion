static inline void json_discard_value_direct (
    struct io_direct* io
)
{
  #define JSON_DISCARD
  #include "../procedures/json_parse_value.c"
  #undef JSON_DISCARD
}



static inline void json_discard_value_buffered (
    struct io_buffered* io
)
{
  #define JSON_DISCARD
  #include "../procedures/json_parse_value.c"
  #undef JSON_DISCARD
}
