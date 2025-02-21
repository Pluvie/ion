static inline void json_decode_primitive (
    struct io* source,
    struct object* target
)
{
  u64 amount_read = 0;
  enum types primitive_type = target->reflection->type;

  switch (primitive_type) {
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
    amount_read = json_parse_number(source, primitive_type, target->address);
    if (error.occurred)
      return reflect_failure(target->reflection);

    if (amount_read == 0) {
      fail("[%s] expected a number", target->name);
      return reflect_failure(target->reflection);
    }

    io_read(source, NULL, amount_read);
    if (error.occurred)
      return reflect_failure(target->reflection);

    break;

  case BYTE:
  case CHAR:
    fail("[%s] CHAR and BYTE types not yet implemented.", target->name);
    break;

  case BOOL:
    amount_read = json_parse_bool(source);
    if (error.occurred)
      return;

    switch (amount_read) {
    case 4:
      memcpy(target->address, &(bool) { true }, sizeof(bool));
      break;
    case 5:
      memcpy(target->address, &(bool) { false }, sizeof(bool));
      break;
    default:
      fail("[%s] expected a boolean", target->name);
      return reflect_failure(target->reflection);
    }

    io_read(source, NULL, amount_read);
    if (error.occurred)
      return reflect_failure(target->reflection);

    break;

  default:
    return;
  }
  
  reflect_validate(target->reflection, target->address);
  if (error.occurred)
    return reflect_failure(target->reflection);
}
