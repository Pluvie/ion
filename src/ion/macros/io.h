/**
 * Creates a new io with channel that depends on the given argument. */
#define io(v, ...)                    \
  _Generic(v,                         \
    void* : io_open_memory,           \
    string : io_open_string,          \
    struct file* : io_open_file,      \
    struct pipe* : io_open_pipe,      \
    struct socket* : io_open_socket,  \
    struct stream* : io_open_stream   \
  )(v, 0 __VA_OPT__(+(__VA_ARGS__)))
