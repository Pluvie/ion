#define io_contains(io_ptr, v, len)             \
  _Generic((io_ptr),                            \
    struct io_direct* : io_contains_direct,     \
    struct io_buffered* : io_contains_buffered  \
  )(io_ptr, v, len)



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
