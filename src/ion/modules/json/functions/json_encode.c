#ifdef ION_INCLUDED
static inline
#endif

void json_encode (
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
    json_encode_primitive(obj, io, rfx);
    return;

  case STRING:
    json_encode_string(obj, io, rfx);
    return;

  case STRUCT:
    json_encode_struct(obj, io, rfx);
    return;

  case POINTER:
    json_encode_pointer(obj, io, rfx);
    return;

  case SEQUENCE:
    json_encode_sequence(obj, io, rfx);
    return;

  case ARRAY:
    json_encode_array(obj, io, rfx);
    return;

  case VECTOR:
    json_encode_vector(obj, io, rfx);
    return;
  }
}
