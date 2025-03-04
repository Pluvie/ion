static inline void binary_decode_primitive (
    struct io* source,
    struct object* target
)
{
  enum types primitive_type = target->reflection->type;
  u32 primitive_type_size = type_sizes[primitive_type];

  void* primitive_value = io_read(source, primitive_type_size);
  if (error.occurred)
    return error_add_reflection_path(target->reflection);

  if (primitive_type == BOOL) {
    /* Special case for booleans: any value other than 0 is forced as `true`. */
    if (*(u8*) primitive_value > 0)
      memcpy(target->address, &(bool) { true }, primitive_type_size);
    else
      memcpy(target->address, &(bool) { false }, primitive_type_size);

  } else {
    memcpy(target->address, primitive_value, primitive_type_size);
  }

  reflect_validate(target->reflection, target->address);
  if (error.occurred)
    return error_add_reflection_path(target->reflection);
}
