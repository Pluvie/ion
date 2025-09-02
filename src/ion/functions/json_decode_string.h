#define json_decode_string(io, rfx, result)             \
  _Generic((io),                                        \
    struct io_direct* : json_decode_string_direct,      \
    struct io_buffered* : json_decode_string_buffered   \
  )(io, rfx, result)



static inline void json_decode_string_direct (
    struct io_direct* io,
    struct reflection* rfx,
    void* target
);



static inline void json_decode_string_buffered (
    struct io_buffered* io,
    struct reflection* rfx,
    void* target
);
