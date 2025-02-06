#ifdef ION_INCLUDED
static inline
#endif

void json_decode (
    struct io* input,
    struct io* output,
    struct protocol* json
)
{
  if (json->debug)
    protocol_debug_pre(input, output, json);

  switch (json->reflection->type) {
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
    json_decode_number(input, output, json);
    break;
  case BYTE:
  case CHAR:
    //json_decode_primitive_char(input, output, json);
    break;
  case BOOL:
    //json_decode_primitive_boolean(input, output, json);
    break;

  case STRUCT:
    json_decode_struct(input, output, json);
    break;

  case ARRAY:
    //json_decode_array(input, output, json);
    break;

  case POINTER:
    //json_decode_pointer(input, output, json);
    break;

  case SEQUENCE:
    //json_decode_sequence(input, output, json);
    break;
  }

  if (json->debug)
    protocol_debug_post(input, output, json);
}
