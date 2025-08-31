void json_decode (
    struct io* io,
    void* target
)
{
  switch (io->type) {
  case IO_DIRECT:
    return json_decode_direct(&(io->direct), target);
  case IO_BUFFERED:
    return json_decode_buffered(&(io->buffered), target);
  default:
    fail("json decode: unrecognized io type");
  }
}


static inline void json_decode_direct (
    struct io_direct* io,
    void* target
)
{
  if (io->rfx != NULL)
    goto decode;
  else
    goto discard;

decode:
  json_parse_spaces(io);

  if (json_parse_null(io, target))
    return;

  switch (io->rfx->type) {
  case INT:
    return json_decode_int(io, target);
  case DEC:
    return json_decode_dec(io, target);
  case BOOL:
    return json_decode_bool(io, target);
  case ENUM:
    return json_decode_enum(io, target);
  case STRING:
    return json_decode_string(io, target);
  case STRUCT:
    return json_decode_struct(io, target);
  case ARRAY:
    return json_decode_array(io, target);
  case POINTER:
    return json_decode_pointer(io, target);
  case SELF:
    return json_decode_self(io, target);
  case LIST:
    return json_decode_list(io, target);
  case SET:
    return json_decode_set(io, target);
  case MAP:
    return json_decode_map(io, target);
  default:
    fail("unsupported reflection type");
  }
  return;

discard:
  json_parse_spaces(io);
  json_discard_value(io);
  return;
}

static inline void json_decode_buffered (
    struct io_buffered* io,
    void* target
)
{
  /* To be implemented. */
  return;
}





static inline struct io io_open_string (
    string* source
)
{
  struct io result = {
    .direct = { .data = source, .cursor = source->pointer },
    .type = IO_DIRECT,
  };
  return result;
}

static inline void io_advance_direct (
    struct io_direct* io,
    int amount
)
{
  if (likely(io->cursor < source->length)) {
    io->cursor += amount;
    return;
  }

  io->cursor = EMPTY_STRING;
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
  if (char_compare(io->cursor, value, length) == 0) {
    io_advance(io, length);
    return true;
  }

  return false;
}

void io_close (
    struct io* io
)
{
  switch (io->type) {
  case IO_DIRECT:
    return;
  case IO_BUFFERED:
    /* To be implemented. */
  default:
    fail("json decode: unrecognized io type");
  }
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
    int number_length = (number_end - io->cursor);
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
    *result = false;
    return true;
  }

  return false;
}



static inline void json_parse_spaces_direct (
    struct io_direct* io
)
{
  while (isspace(*io->cursor))
    io_advance(io, 1);
}








static inline void json_decode_object_direct (
    struct io_direct* io,
    void* target
)
{
  if (unlikely(*io->cursor != '{')) {
    fail("expected object begin");
    return;
  }
  io_advance(io, 1);

parse_field:
  string field_name;
  json_parse_spaces(io);
  bool field_presence = json_parse_string(io, &field_name);
  if (unlikely(!field_presence)) {
    fail("expected object field");
    return;
  }
  /* Here logic to find the field in the rfx. */
  json_parse_spaces(io);

  if (unlikely(*io->cursor != ':')) {
    fail("expected colon after object field");
    return;
  }
  json_parse_spaces(io);

  json_decode_value(io, target); // Change to field_target.
  json_parse_spaces(io);

  switch(*io->cursor) {
  case ',':
    goto parse_field;
  case '}':
    io_advance(io, 1);
    return;
  default:
    if (failure.occurred) return;
    fail("expected comma or object end");
  }

  return;
}


static inline void json_decode_array_direct (
    struct io_direct* io,
    void* target
)
{
  if (unlikely(*io->cursor != '[')) {
    fail("expected array begin");
    return;
  }
  io_advance(io, 1);

parse_value:
  json_decode_value(io, target); // Change to element_target.
  json_parse_spaces(io);

  switch(*io->cursor) {
  case ',':
    goto parse_value;
  case ']':
    io_advance(io, 1);
    return;
  default:
    if (failure.occurred)return;
    fail("expected comma or array end");
  }

  return;
}
