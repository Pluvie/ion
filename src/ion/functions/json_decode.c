#ifdef ION_INCLUDED
static inline
#endif

void json_decode (
    void* obj,
    struct io* io,
    struct reflection* rfx,
    struct memory* allocator
)
{
  if (rfx != NULL)
    goto decode_with_reflection;
  else
    goto discard_value;

decode_with_reflection:
  u64 null_length = json_parse_null(io);
  if (error.occurred)
    return;

  if (null_length > 0)
    goto decode_null_value;

  switch (rfx->type) {
  case U8:
  case U16:
  case U32:
  case U64:
  case I8:
  case I16:
  case I32:
  case I64:
  case D32:
  case D64:
  case D128:
  case BYTE:
  case CHAR:
  case BOOL:
    json_decode_primitive(obj, io, rfx, allocator);
    return;

  case STRING:
    json_decode_string(obj, io, rfx, allocator);
    return;

  case STRUCT:
    json_decode_struct(obj, io, rfx, allocator);
    return;

  case POINTER:
    json_decode_pointer(obj, io, rfx, allocator);
    return;

  case SEQUENCE:
    json_decode_sequence(obj, io, rfx, allocator);
    return;

  case ARRAY:
    json_decode_array(obj, io, rfx, allocator);
    return;

  case VECTOR:
    json_decode_vector(obj, io, rfx, allocator);
    return;
  }

decode_null_value:
  io_read(io, null_length);
  if (error.occurred)
    return;

  memzero(obj, rfx->size);
  return;

discard_value:
  json_parse_spaces(io);
  if (error.occurred)
    return;

  char* character = io_peek(io, sizeof(char));
  if (error.occurred)
    return;

  switch (*character) {
  case '{':
    json_decode_struct(NULL, io, NULL, NULL);
    return;

  case '[':
    json_decode_array(NULL, io, NULL, NULL);
    return;

  case '"':
    u64 string_length = json_parse_string(io);
    if (error.occurred)
      return;

    io_read(io, string_length);
    return;

  case '-':
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
    u64 number_length = json_parse_number(io);
    if (error.occurred)
      return;

    io_read(io, number_length);
    return;

  default:
    u64 value_length = 0;

    value_length = json_parse_bool(io);
    if (error.occurred)
      return;

    if (value_length > 0) {
      io_read(io, value_length);
      return;
    }

    value_length = json_parse_null(io);
    if (error.occurred)
      return;

    if (value_length > 0) {
      io_read(io, value_length);
      return;
    }

    fail("unexpected character `%c`", *character);
    error_add_io_extraction(io);
    return;
  }
}
