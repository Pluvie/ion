#ifdef ION_INCLUDED
static inline
#endif

void binary_encode (
    struct object* source,
    struct io* target
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
    binary_encode_primitive(source, target);
    break;

  case STRUCT:
    binary_encode_struct(source, target);
    break;

  case POINTER:
    //binary_encode_pointer(source, target);
    break;

  case SEQUENCE:
    //binary_encode_sequence(source, target);
    break;

  case ARRAY:
    binary_encode_array(source, target);
    break;

  case VECTOR:
    //binary_encode_vector(source, target);
    break;
  }
}
