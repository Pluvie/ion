static inline void binary_decode_vector (
    struct io* source,
    struct object* target
)
{
read_length:
  u64 vector_length; io_read(source, &vector_length, sizeof(u64));
  if (error.occurred)
    return error_add_reflection_path(target->reflection);

check_minlength:
  u64 vector_minlength = target->reflection->bounds[0];
  if (vector_minlength > 0 && vector_length < vector_minlength) {
    fail("vector required minimum length of %li but found %li",
      vector_minlength, vector_length);
    return error_add_reflection_path(target->reflection);
  }

check_maxlength:
  u64 vector_maxlength = target->reflection->bounds[1];
  if (vector_maxlength > 0 && vector_length > vector_maxlength) {
    fail("vector required maximum length of %li but found %li",
      vector_maxlength, vector_length);
    return error_add_reflection_path(target->reflection);
  }

allocate_vector:
  struct reflect* element_reflection = vector_get(target->reflection->child, 0);
  u64 vector_typesize = reflect_typesize(element_reflection);

  struct vector vector = vector_init(vector_typesize, vector_length, target->allocator);
  vector.length = vector_length;

decode_vector:
  for (u64 i = 0; i < vector.length; i++) {
    element_reflection->index = i;
    struct object element = {
      .reflection = element_reflection,
      .address = vector.data + (i * vector_typesize),
      .allocator = target->allocator
    };
    binary_decode(source, &element);
    if (error.occurred)
      return;
  }

validate_vector:
  reflect_validate(target->reflection, &vector);
  if (error.occurred)
    return error_add_reflection_path(target->reflection);

write_target:
  memcpy(target->address, &vector, sizeof(struct vector));
}
