static inline void json_decode_pointer (
    struct io* source,
    struct object* target
)
{
  struct reflect* pointer_reflection = vector_get(target->reflection->child, 0);
  u64 pointer_size = reflect_typesize(pointer_reflection);

  /* Special case: a POINTER size of type CHAR must be explicitly sent, as its
   * length is not fixed and not known a priori. */
  if (pointer_reflection->type == CHAR)
    goto check_string_size;
  else
    goto allocate_pointer;

check_string_size:
  u64 string_max_size = target->reflection->bounds[0];
  u64 string_size = 0;

  string_size = json_parse_string(source);
  if (error.occurred)
    return;

  if (string_size == 0) {
    fail("expected a string");
    error_add_io_extraction(source);
    error_add_reflection_path(target->reflection);
    return;
  }

  if (string_max_size > 0 && string_size > string_max_size) {
    fail("pointer required maximum string size of %li but found %li",
      string_max_size, pointer_size);
    error_add_io_extraction(source);
    return;
  }

  pointer_size = string_size;

allocate_pointer:
  void* pointer_data = memory_alloc(target->allocator, pointer_size);

  if (pointer_reflection->type == CHAR)
    goto pointer_type_char;
  else
    goto pointer_type_other;

pointer_type_char:
  /* Special case: a POINTER of type CHAR is intended to be a nul-terminated string. */
  io_read(source, pointer_data, pointer_size);
  if (error.occurred)
    return;

  goto validate_pointer;

pointer_type_other:
  struct object pointer = {
    .name = target->name,
    .address = pointer_data,
    .reflection = pointer_reflection,
    .allocator = target->allocator,
  };

  binary_decode(source, &pointer);
  if (error.occurred)
    return;

validate_pointer:
  reflect_validate(target->reflection, pointer_data);
  if (error.occurred)
    return error_add_reflection_path(target->reflection);

write_target:
  u64 pointer_address = (u64) pointer_data;
  memcpy(target->address, &pointer_address, sizeof(u64));
}
