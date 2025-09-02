static inline bool json_decode_value_direct (
    struct io_direct* io,
    struct reflection* rfx,
    void* target
)
{
  #include "../procedures/json_parse_value.c"
}



static inline bool json_decode_value_buffered (
    struct io_buffered* io,
    struct reflection* rfx,
    void* target
)
{
  #include "../procedures/json_parse_value.c"
}
