#ifdef ION_INCLUDED
static inline
#endif

void binary_encode (
    void* obj,
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
    binary_encode_primitive(obj, io, rfx);
    break;

  case STRING:
    binary_encode_string(obj, io, rfx);
    break;

  case STRUCT:
    binary_encode_struct(obj, io, rfx);
    break;

  case POINTER:
    binary_encode_pointer(obj, io, rfx);
    break;

  case SEQUENCE:
    binary_encode_sequence(obj, io, rfx);
    break;

  case ARRAY:
    binary_encode_array(obj, io, rfx);
    break;

  case VECTOR:
    binary_encode_vector(obj, io, rfx);
    break;
  }
}
