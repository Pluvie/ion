/**
 * Generic dispatcher for JSON operations based on the type of the source.
 * Used only internally by ⚡️ION⚡️ functions. */
#define json(func, io, source, ...)               \
  _Generic((source),                              \
    string* : json<string>_ ## func,              \
    struct file* : json<struct file>_ ## func     \
  )(io, source __VA_OPT__(, __VA_ARGS__))



/**
 * External entrypoint of ⚡️ION⚡️ for JSON decoding. */
#define json_decode(io, source) \
  json(decode, io, source)

/**
 * External entrypoint of ⚡️ION⚡️ for JSON encoding. */
#define json_encode(io, source) \
  json(encode, io, source)
