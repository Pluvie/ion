static inline void binary_decode_pointer (
    struct io* source,
    struct object* target
)
{
  struct reflect* pointer = vector_get(target->schema->child, 0);
  u64 pointer_size = reflect_typesize(pointer);

  /* Special case: a POINTER size of type CHAR must be explicitly sent, as its
   * length is not fixed and not known a priori. */
  if (pointer->type == CHAR)
    goto check_string_size;
  else
    goto allocate_pointer;

check_string_size:
  u64 string_max_size = target->schema->bounds[0];
  u64* string_size = io_read(source, sizeof(u64));
  if (error.occurred)
    return reflect_failure(target->schema);

  if (string_max_size > 0 && *string_size > string_max_size) {
    fail("pointer required maximum string size of %li but found %li",
      string_max_size, pointer_size);
    return reflect_failure(target->schema);
  }

  pointer_size = *string_size;

allocate_pointer:
  void* pointer_data = memory_alloc(target->allocator, pointer_size);

  if (pointer->type == CHAR)
    goto pointer_type_char;
  else
    goto pointer_type_other;

pointer_type_char:
  /* Special case: a POINTER of type CHAR is intended to be a nul-terminated string. */
  char* string = io_read(source, pointer_size);
  if (error.occurred)
    return;

  memcpy(pointer_data, string, pointer_size);
  goto validate_pointer;

pointer_type_other:
  struct object pointer_object = {
    .name = target->name,
    .address = pointer_data,
    .schema = pointer,
    .allocator = target->allocator,
  };

  binary_decode(source, &pointer_object);
  if (error.occurred)
    return;

validate_pointer:
  reflect_validate(target->schema, pointer_data);
  if (error.occurred)
    return reflect_failure(target->schema);

write_target:
  u64 pointer_address = (u64) pointer_data;
  memcpy(target->address, &pointer_address, sizeof(u64));
}
