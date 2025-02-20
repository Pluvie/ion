#ifdef ION_INCLUDED
static inline
#endif

void json_decode (
    struct io* source,
    struct object* target
)
{
  reflect_initialize(source->reflection);

  switch (source->reflection->type) {
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
    break;

  case STRUCT:
    json_decode_struct(source, target);
    break;

  case POINTER:
    //json_decode_pointer(source, target);
    break;

  case SEQUENCE:
    //json_decode_sequence(source, target);
    break;

  case ARRAY:
    //json_decode_array(source, target);
    break;

  case VECTOR:
    //json_decode_vector(source, target);
    break;
  }
}
