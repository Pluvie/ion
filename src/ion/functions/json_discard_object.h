#define json_discard_object(io)                         \
  _Generic((io),                                        \
    struct io_direct* : json_discard_object_direct,     \
    struct io_buffered* : json_discard_object_buffered  \
  )(io)



static inline bool json_discard_object_direct (
    struct io_direct* io
);



static inline bool json_discard_object_buffered (
    struct io_buffered* io
);
