static inline void csv_decode_column (
    struct string* column,
    struct object* target
)
{
  enum types type = target->reflection->type;
  u32 type_size = type_sizes[type];

  char* string = memory_alloc_zero(target->allocator, column->length + 1);
  snprintf(string, column->length + 1, "%s", column->content);

  switch (type) {
  case U8:
  case U16:
  case U32:
  case U64:
    u64 number_u64 = strtoull(string, NULL, 10);
    memcpy(target->address, &number_u64, type_size);
    break;

  case I8:
  case I16:
  case I32:
  case I64:
    i64 number_i64 = strtoll(string, NULL, 10);
    memcpy(target->address, &number_i64, type_size);

  case D32:
    d32 number_d32 = strtof(string, NULL);
    memcpy(target->address, &number_d32, type_size);
    break;

  case D64:
    d64 number_d64 = strtod(string, NULL);
    memcpy(target->address, &number_d64, type_size);
    break;

  case D128:
    d128 number_128 = strtold(string, NULL);
    memcpy(target->address, &number_128, type_size);
    break;

  case BOOL:
    if (strneq("true", column->content, column->length)) {
      memcpy(target->address, &(bool) { true }, type_size);
      break;
    }
    if (strneq("false", column->content, column->length)) {
      memcpy(target->address, &(bool) { false }, type_size);
      break;
    }

  case POINTER:
    u64 string_address = (u64) string;
    memcpy(target->address, &string_address, type_size);

  default:
    return;
  }

  reflect_validate(target->reflection, target->address);
  if (error.occurred)
    return error_add_reflection_path(target->reflection);
}
