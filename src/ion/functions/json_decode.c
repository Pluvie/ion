#ifdef ION_INCLUDED
static inline
#endif

void json_decode (
    struct io* source,
    struct object* target
)
{
  if (target != NULL)
    goto decode_to_target;
  else
    goto discard_value;

decode_to_target:
  reflect_initialize(target->reflection);

  switch (target->reflection->type) {
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
    json_decode_primitive(source, target);
    return;

  case STRUCT:
    json_decode_struct(source, target);
    return;

  case POINTER:
    //json_decode_pointer(source, target);
    return;

  case SEQUENCE:
    //json_decode_sequence(source, target);
    return;

  case ARRAY:
    //json_decode_array(source, target);
    return;

  case VECTOR:
    //json_decode_vector(source, target);
    return;
  }

discard_value:
  u64 amount_read = 0;
  char character;

  amount_read = json_parse_spaces(source);
  if (amount_read > 0) {
    io_read(source, NULL, amount_read);
    if (error.occurred)
      return;
  }

  io_peek(source, &character, sizeof(char));
  if (error.occurred)
    return;

  switch (character) {
  case '{':
    json_decode_struct(source, NULL);
    if (error.occurred)
      return;

  case '[':
    fail("json_decode_array not yet implemented");
    return;
    //json_decode_array(source, NULL);
    //if (error.occurred)
    //  return;

  case '"':
    amount_read = json_parse_string(source);
    if (error.occurred)
      return;

    io_read(source, NULL, amount_read);
    if (error.occurred)
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
    amount_read = json_parse_number(source, 0, NULL);
    if (error.occurred)
      return;

    io_read(source, NULL, amount_read);
    if (error.occurred)
      return;

  default:
    amount_read = json_parse_bool(source);
    if (error.occurred)
      return;

    if (amount_read > 0) {
      io_read(source, NULL, amount_read);
      return;
    }

    amount_read = json_parse_null(source);
    if (error.occurred)
      return;

    if (amount_read > 0) {
      io_read(source, NULL, amount_read);
      return;
    }

    fail("unexpected character `%c`", character);
    return;
  }
}
