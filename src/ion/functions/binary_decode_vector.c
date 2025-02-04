static inline void binary_decode_vector (
    struct io* source,
    struct object* target
)
{
read_length:
  u64* vector_length = io_read(source, sizeof(u64));
  if (error.occurred)
    return reflect_failure(target->schema);

check_minlength:
  u64 vector_minlength = target->schema->bounds[0];
  if (vector_minlength > 0 && *vector_length < vector_minlength) {
    fail("vector required minimum length of %li but found %li",
      vector_minlength, *vector_length);
    return reflect_failure(target->schema);
  }

check_maxlength:
  u64 vector_maxlength = target->schema->bounds[1];
  if (vector_maxlength > 0 && *vector_length > vector_maxlength) {
    fail("vector required maximum length of %li but found %li",
      vector_maxlength, *vector_length);
    return reflect_failure(target->schema);
  }

allocate_vector:
  struct reflect* element = vector_get(target->schema->child, 0);
  u64 vector_typesize = reflect_typesize(element);

  struct vector vector = vector_init(vector_typesize, *vector_length, target->allocator);
  vector.length = *vector_length;

decode_vector:
  for (u64 i = 0; i < vector.length; i++) {
    element->index = i;
    struct object element_object = {
      .schema = element,
      .address = vector.data + (i * vector_typesize),
      .allocator = target->allocator
    };
    binary_decode(source, &element_object);
    if (error.occurred)
      return;
  }

validate_vector:
  reflect_validate(target->schema, &vector);
  if (error.occurred)
    return reflect_failure(target->schema);

write_target:
  memcpy(target->address, &vector, sizeof(struct vector));
}
