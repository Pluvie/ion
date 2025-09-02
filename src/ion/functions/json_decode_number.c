static inline void json_decode_number_direct (
    struct io_direct* io,
    struct reflection* rfx,
    void* target
)
{
  #include "../procedures/json_parse_number.c"
}



static inline void json_decode_number_buffered (
    struct io_buffered* io,
    struct reflection* rfx,
    void* target
)
{
  io_reserve(io, 128);
  #include "../procedures/json_parse_number.c"
}
