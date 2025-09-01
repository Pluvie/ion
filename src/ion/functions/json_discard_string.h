#define json_discard_string(io)                         \
  _Generic((io),                                        \
    struct io_direct* : json_discard_string_direct,     \
    struct io_buffered* : json_discard_string_buffered  \
  )(io)



static inline bool json_discard_string_direct (
    struct io_direct* io
);



static inline bool json_discard_string_buffered (
    struct io_buffered* io
);
