#define json_discard_value(io)                          \
  _Generic((io),                                        \
    struct io_direct* : json_discard_value_direct,      \
    struct io_buffered* : json_discard_value_buffered   \
  )(io)



static inline bool json_discard_value_direct (
    struct io_direct* io
);



static inline bool json_discard_value_buffered (
    struct io_buffered* io
);
