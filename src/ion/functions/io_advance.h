#define io_advance(io_ptr, amount)              \
  _Generic((io_ptr),                            \
    struct io_direct* : io_advance_direct,      \
    struct io_buffered* : io_advance_buffered   \
  )(io_ptr, amount)



static inline void io_advance_direct (
    struct io_direct* io,
    int amount
);




static inline void io_advance_buffered (
    struct io_buffered* io,
    int amount
);
