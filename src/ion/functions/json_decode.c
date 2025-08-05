void json_decode (
    void* obj,
    struct io* io,
    struct reflection* rfx,
    struct memory* allocator
)
{
  if (rfx != NULL)
    goto decode_with_reflection;
  else
    goto decode_and_discard;

decode_with_reflection:
  if (json_decode_null(obj, io, rfx))
    return;

  switch (rfx->type) {
  case INT:
    //return json_decode_int(obj, io, rfx, allocator);
  case DEC:
  case CHAR:
  case BOOL:
  case ENUM:
  case STRING:
  case STRUCT:
    //return json_decode_struct(obj, io, rfx, allocator);
  case ARRAY:
  case POINTER:
  case SELF:
  case LIST:
  case MAP:
  case SET:
    return;
  }

decode_and_discard:
  return;
}
