void json_decode (
    struct io* io,
    void* target
)
{
  switch (io.type) {
  case IO_DIRECT:
    return json_decode_direct(&(io.direct), target);
  case IO_BUFFERED:
    return json_decode_buffered(&(io.direct), target);
  default:
    fail("json decode: unrecognized io type");
  }
}


#define json_parse_spaces(io_ptr)                   \
  _Generic((io_ptr),                                \
    struct io_direct* : json_parse_spaces_direct    \
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


static inline void json_decode_direct (
    struct io_direct* io,
    void* target
)
{
  if (io->rfx != NULL)
    goto decode_with_reflection;
  else
    goto parse_and_discard;

decode_with_reflection:
  /* To be implemented. */
  return;

parse_and_discard:
  json_parse_spaces(io);

  switch(*io->cursor) {
  case '{':
    return json_discard_object(io);

  case '[':
    return json_discard_array(io);

  default:
    if (json_discard_string(io))
      return;

    if (json_discard_number(io))
      return;

    if (json_discard_bool(io))
      return;

    if (json_discard_null(io))
      return;

    if (failure.occurred)
      return;

    fail("expected a json value");
    return;
  }
}

static inline void json_decode_buffered (
    struct io_buffered* io,
    void* target
)
{
  /* To be implemented. */
  return;
}





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

static inline void io_advance_direct (
    struct io_direct* io,
    int amount
)
{
  io->cursor += amount;
  return;
}

static inline void io_reserve_direct (
    struct io_direct* io,
    int amount
)
{
  return;
}

static inline bool io_contains_direct (
    struct io_direct* io,
    void* value,
    int length
)
{
  if (byte_eq(io->cursor, value, length)) {
    io_advance(io, length);
    return true;
  }

  return false;
}
  















static inline bool json_parse_string_direct (
    struct io_direct* io
)
{
  bool escaped = false;
  io->result.pointer = io->cursor;

  if (*io->cursor != '"')
    goto error;

read_character:
  io_advance(io, 1);

  if (escaped) {
    escaped = false;
    goto read_character;
  }

  if (*io->cursor == 92) {
    escaped = true;
    goto read_character;
  }

  if (*io->cursor == '"')
    goto terminate;

  if (unlikely(io_exhausted(io)))
    goto error;

  goto read_character;

terminate:
  io->result.length = io->cursor - io->result.pointer;
  return;

error:
  *io->result = (string) { 0 };
  io_cursor_restore(io, cursor);
  return;
}



static inline bool json_parse_number_direct (
    struct io_direct* io,
    dec* result
)
{
  io_reserve(io, 128);
  char* number_end;

  *result = strtold(io->cursor, &number_end);
  if (errno == 0) {
    int number_length = (end - data);
    io_advance(io, number_length);
    return true;
  }

  return false;
}



static inline bool json_parse_null_direct (
    struct io_direct* io
)
{
  if (io_contains(io, "null", lengthof("null")))
    return true;

  return false;
}



static inline bool json_parse_bool_direct (
    struct io_direct* io,
    bool* result
)
{
  if (io_contains(io, "true", lengthof("true"))) {
    *result = true;
    return true;
  }

  if (io_contains(io, "false", lengthof("false"))) {
    #ifdef store_result
      *result = false;
    #endif
    return true;
  }

  return false;
}



static inline bool json_parse_spaces_direct (
    struct io_direct* io
)
{
  while (isspace(*io->cursor))
    io_advance(io, 1);
}
