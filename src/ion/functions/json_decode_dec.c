static inline void json_decode_dec_direct (
    struct io_direct* io,
    struct reflection* rfx,
    void* target
)
{
  #define JSON_DECODE_DEC
  #include "../procedures/json_parse_number.c"
  #undef JSON_DECODE_DEC
}



static inline void json_decode_dec_buffered (
    struct io_buffered* io,
    struct reflection* rfx,
    void* target
)
{
  io_reserve(io, 128);
  #define JSON_DECODE_DEC
  #include "../procedures/json_parse_number.c"
  #undef JSON_DECODE_DEC
}
