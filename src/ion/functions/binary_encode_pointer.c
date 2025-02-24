static inline void binary_encode_pointer (
    struct object* source,
    struct io* target
)
{
  struct reflect* pointer_reflection = vector_get(source->reflection->child, 0);
  u64 pointer_size = reflect_typesize(pointer_reflection);
  void* pointer_address = *(void**) source->address;

  /* Special case: a POINTER size of type CHAR must be explicitly sent, as its
   * length is not fixed and not known a priori. */
  if (pointer_reflection->type == CHAR)
    goto check_string_size;
  else
    goto encode_pointer;

check_string_size:
  u64 string_max_size = source->reflection->bounds[0];
  u64 string_size = strlen(pointer_address) + 1;

  if (string_max_size > 0 && string_size > string_max_size) {
    fail("pointer required maximum string size of %li but found %li",
      string_max_size, pointer_size);
    return error_add_reflection_path(source->reflection);
  }

encode_length:
  io_write(target, &string_size, sizeof(string_size));
  if (error.occurred)
    return error_add_reflection_path(source->reflection);

encode_string:
  io_write(target, pointer_address, string_size);
  if (error.occurred)
    return error_add_reflection_path(source->reflection);

  return;

encode_pointer:
  struct object pointer = {
    .name = source->name,
    .address = pointer_address,
    .reflection = pointer_reflection,
  };

  binary_encode(&pointer, target);
  if (error.occurred)
    return;
}
