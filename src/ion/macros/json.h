#define json_decode_value(io_ptr, target)           \
  _Generic((io_ptr),                                \
    struct io_direct* : json_decode_direct          \
  )(io_ptr, target)

#define json_parse_spaces(io_ptr)                   \
  _Generic((io_ptr),                                \
    struct io_direct* : json_parse_spaces_direct    \
  )(io_ptr)


#define json_discard_value(io_ptr)                  \
  _Generic((io_ptr),                                \
    struct io_direct* : json_discard_value_direct   \
  )(io_ptr)

#define json_discard_object(io_ptr)                 \
  _Generic((io_ptr),                                \
    struct io_direct* : json_discard_object_direct  \
  )(io_ptr)

#define json_discard_array(io_ptr)                  \
  _Generic((io_ptr),                                \
    struct io_direct* : json_discard_array_direct   \
  )(io_ptr)

#define json_discard_string(io_ptr)                 \
  _Generic((io_ptr),                                \
    struct io_direct* : json_discard_string_direct  \
  )(io_ptr)

#define json_discard_number(io_ptr)                 \
  _Generic((io_ptr),                                \
    struct io_direct* : json_discard_number_direct  \
  )(io_ptr)

#define json_discard_bool(io_ptr)                   \
  _Generic((io_ptr),                                \
    struct io_direct* : json_discard_bool_direct    \
  )(io_ptr)

#define json_discard_null(io_ptr)                   \
  _Generic((io_ptr),                                \
    struct io_direct* : json_discard_null_direct    \
  )(io_ptr)
