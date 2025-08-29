/**
 * Generic dispatcher for json operations based on the type of the source. */
#define json(func, io, source, ...)               \
  _Generic((source),                              \
    string* : json<string>_ ## func,              \
    struct file* : json<struct file>_ ## func     \
  )(io, source __VA_OPT__(, __VA_ARGS__))
