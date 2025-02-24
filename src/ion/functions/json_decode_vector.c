static inline void json_decode_vector (
    struct io* source,
    struct object* target
)
{
  if (target == NULL)
    return json_decode_array(source, target);

decode_as_array:
  struct reflect* element_reflection = vector_get(target->reflection->child, 0);
  u64 element_typesize = reflect_typesize(element_reflection);
  struct array array = array_init(element_typesize, 0, target->allocator);

  struct reflect array_reflection;
  memcpy(&array_reflection, target->reflection, sizeof(struct reflect));
  array_reflection.type = ARRAY;
  array_reflection.bounds[0] = 0;
  array_reflection.bounds[1] = 0;

  struct object array_object = {
    .name = target->name,
    .address = &array,
    .reflection = &array_reflection,
    .allocator = target->allocator,
  };

  json_decode_array(source, &array_object);
  if (error.occurred)
    return;

convert_to_vector:
  struct vector vector = vector_from_array(&array);

check_length:
  u64 vector_minlength = target->reflection->bounds[0];
  u64 vector_maxlength = target->reflection->bounds[1];

  if (vector_minlength > 0 && vector.length < vector_minlength) {
    fail("vector required minimum length of %li", vector_minlength);
    error_add_io_extraction(source);
    return error_add_reflection_path(target->reflection);
  }

  if (vector_maxlength > 0 && vector.length >= vector_maxlength) {
    fail("vector required maximum length of %li", vector_maxlength);
    error_add_io_extraction(source);
    return error_add_reflection_path(target->reflection);
  }

terminate:
  reflect_validate(target->reflection, &vector);
  if (error.occurred)
    return error_add_reflection_path(target->reflection);

  memcpy(target->address, &vector, sizeof(struct vector));
}
