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
    return json_decode_dec(obj, io, rfx, allocator);
  case BOOL:
    return json_decode_bool(obj, io, rfx, allocator);
  case ENUM:
    return json_decode_enum(obj, io, rfx, allocator);
  case STRING:
    return json_decode_string(obj, io, rfx, allocator);
  case STRUCT:
    return json_decode_struct(obj, io, rfx, allocator);
  case ARRAY:
    return json_decode_array(obj, io, rfx, allocator);
  case POINTER:
    return json_decode_pointer(obj, io, rfx, allocator);
  case SELF:
    return json_decode_self(obj, io, rfx, allocator);
  case LIST:
    return json_decode_list(obj, io, rfx, allocator);
  case SET:
    return json_decode_set(obj, io, rfx, allocator);
  case MAP:
    return json_decode_map(obj, io, rfx, allocator);
  }

decode_and_discard:
  int result = 0;

  if (json_decode_null(obj, io, rfx))
    return;

  result = json_parse_number(io);
  if (unlikely(failure.occurred))
    return;
  if (result > 0)
    return;

  result = json_parse_string(io);
  if (unlikely(failure.occurred))
    return;
  if (result > 0)
    return;

  result = json_parse_bool(io);
  if (unlikely(failure.occurred))
    return;
  if (result > 0)
    return;

  io_peek(io, sizeof(char));
  if (unlikely(failure.occurred))
    return;

  switch (string_char_at(io->result, 0)) {
  case '{':
    return json_decode_struct(NULL, io, NULL, NULL);
  case '[':
    return json_decode_array(NULL, io, NULL, NULL);
  default:
    fail("expected a json value");
    failure_add_reflection_info(rfx);
    failure_add_io_info(io);
  }

  return;
}
