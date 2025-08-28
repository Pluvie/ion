#define io(source, rfx, allocator)      \
  _Generic((source),                    \
    string* : io_init,                  \
    struct file* : io_init_with_buffer  \
  )(rfx, allocator);

#define io_read(v, source, amount, ...)       \
  _Generic((source),                          \
    string* : io<string>_read,                \
    struct file* : io<struct file>_read       \
  )(v, source, amount __VA_OPT__(, __VA_ARGS__));
