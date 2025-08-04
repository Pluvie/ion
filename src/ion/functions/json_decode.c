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
  int null_length = json_parse_null(io);
  if (error.occurred)
    return;

  if (null_length > 0) {
    io_read(io, null_length);
    if (error.occurred)
      return;

    memzero(obj, rfx->size);
    return;
  }

  switch (rfx->type) {
  case INT:
    return json_decode_int(obj, io, rfx, allocator);
  case DEC:
  case CHAR:
  case BOOL:
  case ENUM:
  case STRING:
  case STRUCT:
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
