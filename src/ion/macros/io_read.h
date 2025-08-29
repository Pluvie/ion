/**
 * Generic dispatcher for io read operations based on the type of the source. */
#define io_read(io_ptr, source, amount)       \
  _Generic((source),                          \
    string* : io<string>_read,                \
    struct file* : io<struct file>_read,      \
    struct pipe* : io<struct pipe>_read,      \
    struct socket* : io<struct socket>_read,  \
    struct stream* : io<struct stream>_read   \
  )(io_ptr, source, amount)
