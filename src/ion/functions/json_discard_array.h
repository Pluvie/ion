#define json_discard_array(io)                          \
  _Generic((io),                                        \
    struct io_direct* : json_discard_array_direct,      \
    struct io_buffered* : json_discard_array_buffered   \
  )(io)



static inline bool json_discard_array_direct (
    struct io_direct* io
);



static inline bool json_discard_array_buffered (
    struct io_buffered* io
);
