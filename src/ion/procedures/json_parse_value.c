#ifdef JSON_DISCARD
  #include "json_parse_spaces.c"

  switch(*io->cursor) {
  case '{':
    return json_discard_object(io);
  
  case '[':
    return json_discard_array(io);
  
  default:
    if (json_discard_string(io))
      return true;
  
    if (json_discard_number(io))
      return true;
  
    if (json_discard_bool(io))
      return true;
  
    if (json_discard_null(io))
      return true;
  
    if (unlikely(failure.occurred))
      return false;
  
    fail("expected a json value");
    failure_add_io_info(io);
    return false;
  }

#else
  /*
  #include "json_parse_spaces.c"

  if (json_decode_null(io, target))
    return true;
  
  switch (io->rfx->type) {
  case INT:
    return json_decode_int(io, target);
  case DEC:
    return json_decode_dec(io, target);
  case BOOL:
    return json_decode_bool(io, target);
  case ENUM:
    return json_decode_enum(io, target);
  case STRING:
    return json_decode_string(io, target);
  case STRUCT:
    return json_decode_struct(io, target);
  case ARRAY:
    return json_decode_array(io, target);
  case POINTER:
    return json_decode_pointer(io, target);
  case SELF:
    return json_decode_self(io, target);
  case LIST:
    return json_decode_list(io, target);
  case SET:
    return json_decode_set(io, target);
  case MAP:
    return json_decode_map(io, target);
  default:
    fail("unsupported reflection type");
  }
  */

  return false;
  
#endif
