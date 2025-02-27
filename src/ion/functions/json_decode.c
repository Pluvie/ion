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
    json_decode_pointer(source, target);
    return;

  case SEQUENCE:
    json_decode_sequence(source, target);
    return;

  case ARRAY:
    json_decode_array(source, target);
    return;

  case VECTOR:
    json_decode_vector(source, target);
    return;
  }

discard_value:
  json_parse_spaces(source);
  if (error.occurred)
    return;

  char* character = io_read(source, sizeof(char));
  if (error.occurred)
    return;
  source->cursor -= source->read_amount;

  switch (*character) {
  case '{':
    json_decode_struct(source, NULL);
    return;

  case '[':
    json_decode_array(source, NULL);
    return;

  case '"':
    json_parse_string(source, NULL);
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
    struct sci_notation number;
    json_parse_number(source, &number);
    return;

  default:
    if (json_parse_bool(source, NULL))
      return;

    if (error.occurred)
      return;

    if (json_parse_null(source))
      return;

    if (error.occurred)
      return;

    fail("unexpected character `%c`", *character);
    error_add_io_extraction(source);
    return;
  }
}
