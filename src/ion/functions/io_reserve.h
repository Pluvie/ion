#define io_reserve(io_ptr, amount)              \
  _Generic((io_ptr),                            \
    struct io_direct* : io_reserve_direct,      \
    struct io_buffered* : io_reserve_buffered   \
  )(io_ptr, amount)



static inline void io_reserve_direct (
    struct io_direct* io,
    int amount
);



static inline void io_reserve_buffered (
    struct io_buffered* io,
    int amount
);
