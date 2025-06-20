/**
 * Creates a new io with channel that depends on the given argument. */
#define io(v, ...)                  \
  _Generic(v,                       \
    int : io_open_descriptor,       \
    int32 : io_open_descriptor,     \
    void* : io_open_memory,         \
    FILE* : io_open_stream,         \
    slice : io_open_slice,          \
    string : io_open_string         \
  )(v, 0 __VA_OPT__(+(__VA_ARGS__)))

