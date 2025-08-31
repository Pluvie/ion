#define json_decode_value(io, target)                   \
  _Generic((io),                                        \
    struct io_direct* : json_decode_value_direct,       \
    struct io_buffered* : json_decode_value_buffered    \
  )(io, target)



static inline void json_decode_value_direct (
    struct io_direct* io,
    void* target
);



static inline void json_decode_value_buffered (
    struct io_buffered* io,
    void* target
);
