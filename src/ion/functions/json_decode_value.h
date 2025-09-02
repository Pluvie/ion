#define json_decode_value(io, rfx, target)              \
  _Generic((io),                                        \
    struct io_direct* : json_decode_value_direct,       \
    struct io_buffered* : json_decode_value_buffered    \
  )(io, rfx, target)



static inline bool json_decode_value_direct (
    struct io_direct* io,
    struct reflection* rfx,
    void* target
);



static inline bool json_decode_value_buffered (
    struct io_buffered* io,
    struct reflection* rfx,
    void* target
);
