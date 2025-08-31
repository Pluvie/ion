static inline struct io io_open_string (
    string* source
);
void io_close (
    struct io* io
);
static inline void json_parse_spaces_direct (
    struct io_direct* io
);
static inline void json_decode_object_direct (
    struct io_direct* io,
    void* target
);
static inline void json_decode_array_direct (
    struct io_direct* io,
    void* target
);



#define io_open(source)                         \
  _Generic((source),                            \
    string* : io_open_string                    \
  )(source)
#define io_advance(io_ptr, amount)              \
  _Generic((io_ptr),                            \
    struct io_direct* : io_advance_direct       \
  )(io_ptr, amount)
#define io_reserve(io_ptr, amount)              \
  _Generic((io_ptr),                            \
    struct io_direct* : io_reserve_direct       \
  )(io_ptr, amount)
#define io_exhausted(io_ptr)                    \
  *((io_ptr)->cursor) == 0
#define io_cursor_restore(io_ptr, prev)         \
  (io_ptr)->cursor = prev
#define io_contains(io_ptr, v, len)             \
  _Generic((io_ptr),                            \
    struct io_direct* : io_contains_direct      \
  )(io_ptr, v, len)
