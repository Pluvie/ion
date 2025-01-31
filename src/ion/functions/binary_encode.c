#ifdef ION_INCLUDED
static inline
#endif

void binary_encode (
    struct protocol* encoder
)
{
  switch (encoder->schema->type) {
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
    binary_encode_primitive(encoder);
    break;

  case STRUCT:
    binary_encode_struct(encoder);
    break;

  case POINTER:
    //binary_encode_pointer(encoder);
    break;

  case SEQUENCE:
    //binary_encode_sequence(encoder);
    break;

  case ARRAY:
    //binary_encode_array(encoder);
    break;

  case VECTOR:
    //binary_encode_vector(encoder);
    break;
  }
}
