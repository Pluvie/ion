static inline void json_decode_primitive (
    struct io* source,
    struct object* target
)
{
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
    struct sci_notation number;
    bool is_number = json_parse_number(source, &number);
    if (error.occurred)
      return error_add_reflection_path(target->reflection);

    if (!is_number) {
      fail("expected a number");
      error_add_io_extraction(source);
      error_add_reflection_path(target->reflection);
      return;
    }

    sci_notation_convert(&number, primitive_type, target->address);
    if (error.occurred) {
      error_add_io_extraction(source);
      error_add_reflection_path(target->reflection);
      return;
    }

    break;

  case BOOL:
    bool is_bool = json_parse_bool(source, target->address);
    if (error.occurred)
      return;

    if (!is_bool) {
      fail("expected a boolean");
      error_add_io_extraction(source);
      error_add_reflection_path(target->reflection);
      return;
    }

    break;

  default:
    fail("primitive type `%s` not supported", type_names[primitive_type]);
    error_add_io_extraction(source);
    error_add_reflection_path(target->reflection);
    return;
  }
  
  reflect_validate(target->reflection, target->address);
  if (error.occurred)
    return error_add_reflection_path(target->reflection);
}
