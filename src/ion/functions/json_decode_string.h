#define json_decode_string(io, result)                  \
  _Generic((io),                                        \
    struct io_direct* : json_decode_string_direct,      \
    struct io_buffered* : json_decode_string_buffered   \
  )(io, result)



static inline void json_decode_string_direct (
    struct io_direct* io,
    string* result
);



static inline void json_decode_string_buffered (
    struct io_buffered* io,
    string* result
);
