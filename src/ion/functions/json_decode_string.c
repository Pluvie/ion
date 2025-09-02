static inline void json_decode_string_direct (
    struct io_direct* io,
    struct reflection* rfx,
    void* target
)
{
  #include "../procedures/json_parse_string.c"
}



static inline void json_decode_string_buffered (
    struct io_buffered* io,
    struct reflection* rfx,
    void* target
)
{
  #include "../procedures/json_parse_string.c"
}
