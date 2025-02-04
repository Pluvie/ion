#ifdef ION_INCLUDED
static inline
#endif

void binary_decode (
    struct io* source,
    struct object* target
)
{
  reflect_initialize(target->schema);

  switch (target->schema->type) {
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
    binary_decode_primitive(source, target);
    break;

  case STRUCT:
    binary_decode_struct(source, target);
    break;

  case POINTER:
    binary_decode_pointer(source, target);
    break;

  case SEQUENCE:
    binary_decode_sequence(source, target);
    break;

  case ARRAY:
    binary_decode_array(source, target);
    break;

  case VECTOR:
    binary_decode_vector(source, target);
    break;
  }
}
