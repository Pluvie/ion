#define json_discard_null(io)                           \
  _Generic((io),                                        \
    struct io_direct* : json_discard_null_direct,       \
    struct io_buffered* : json_discard_null_buffered    \
  )(io)



static inline bool json_discard_null_direct (
    struct io_direct* io
);



static inline bool json_discard_null_buffered (
    struct io_buffered* io
);
