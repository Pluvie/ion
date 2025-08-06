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
    return json_decode_int(obj, io, rfx, allocator);
  case DEC:
  case CHAR:
  case BOOL:
  case ENUM:
    return json_decode_int(obj, io, rfx, allocator);
  case STRING:
    return json_decode_string(obj, io, rfx, allocator);
  case STRUCT:
    return json_decode_struct(obj, io, rfx, allocator);
  case ARRAY:
  case POINTER:
  case SELF:
  case LIST:
  case MAP:
  case SET:
    return;
  }

decode_and_discard:
  int parsed_length = 0;

  if (json_decode_null(obj, io, rfx))
    return;

  parsed_length = json_parse_number(io);
  if (error.occurred)
    return;
  if (parsed_length > 0) {
    io_read(io, parsed_length);
    return;
  }

  parsed_length = json_parse_string(io);
  if (error.occurred)
    return;
  if (parsed_length > 0) {
    io_read(io, parsed_length);
    return;
  }

  return;
}
