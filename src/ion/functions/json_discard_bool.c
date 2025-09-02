static inline bool json_discard_bool_direct (
    struct io_direct* io
)
{
  #define JSON_DISCARD
  #include "../procedures/json_parse_bool.c"
  #undef JSON_DISCARD
}



static inline bool json_discard_bool_buffered (
    struct io_buffered* io
)
{
  #define JSON_DISCARD
  #include "../procedures/json_parse_bool.c"
  #undef JSON_DISCARD
}
