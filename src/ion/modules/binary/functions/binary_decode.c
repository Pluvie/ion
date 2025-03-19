#ifdef ION_INCLUDED
static inline
#endif

void binary_decode (
    void* obj,
    struct io* io,
    struct reflection* rfx,
    struct memory* allocator
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
    binary_decode_primitive(obj, io, rfx, allocator);
    break;

  case STRING:
    binary_decode_string(obj, io, rfx, allocator);
    break;

  case STRUCT:
    binary_decode_struct(obj, io, rfx, allocator);
    break;

  case POINTER:
    binary_decode_pointer(obj, io, rfx, allocator);
    break;

  case SEQUENCE:
    binary_decode_sequence(obj, io, rfx, allocator);
    break;

  case ARRAY:
    binary_decode_array(obj, io, rfx, allocator);
    break;

  case VECTOR:
    binary_decode_vector(obj, io, rfx, allocator);
    break;
  }
}
