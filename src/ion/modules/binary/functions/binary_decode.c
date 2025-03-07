#ifdef ION_INCLUDED
static inline
#endif

void binary_decode (
    struct io* io,
    struct reflection* rfx
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
    binary_decode_primitive(io, rfx);
    break;

  case STRING:
    binary_decode_string(io, rfx);
    break;

  case STRUCT:
    binary_decode_struct(io, rfx);
    break;

  case POINTER:
    binary_decode_pointer(io, rfx);
    break;

  case SEQUENCE:
    binary_decode_sequence(io, rfx);
    break;

  case ARRAY:
    binary_decode_array(io, rfx);
    break;

  case VECTOR:
    binary_decode_vector(io, rfx);
    break;
  }
}
