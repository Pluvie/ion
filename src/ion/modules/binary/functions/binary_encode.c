#ifdef ION_INCLUDED
static inline
#endif

void binary_encode (
    struct reflection* rfx,
    struct io* io
)
{
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
    binary_encode_primitive(rfx, io);
    break;

  case STRING:
    binary_encode_string(rfx, io);
    break;

  case STRUCT:
    binary_encode_struct(rfx, io);
    break;

  case POINTER:
    binary_encode_pointer(rfx, io);
    break;

  case SEQUENCE:
    binary_encode_sequence(rfx, io);
    break;

  case ARRAY:
    binary_encode_array(rfx, io);
    break;

  case VECTOR:
    binary_encode_vector(rfx, io);
    break;
  }
}
