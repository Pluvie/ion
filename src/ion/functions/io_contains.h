#define io_contains(io, value, length)          \
  _Generic((io),                                \
    struct io_direct* : io_contains_direct,     \
    struct io_buffered* : io_contains_buffered  \
  )(io, value, length)



static inline bool io_contains_direct (
    struct io_direct* io,
    void* value,
    int length
);



static inline bool io_contains_buffered (
    struct io_buffered* io,
    void* value,
    int length
);
