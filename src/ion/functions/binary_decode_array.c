static inline void binary_decode_array (
    struct io* source,
    struct object* target
)
{
read_length:
  u64* array_length = io_read(source, sizeof(u64));
  if (error.occurred)
    return reflect_failure(target->schema);

check_minlength:
  u64 array_minlength = target->schema->bounds[0];
  if (array_minlength > 0 && *array_length < array_minlength) {
    fail("array required minimum length of %li but found %li",
      array_minlength, *array_length);
    return reflect_failure(target->schema);
  }

check_maxlength:
  u64 array_maxlength = target->schema->bounds[1];
  if (array_maxlength > 0 && *array_length > array_maxlength) {
    fail("array required maximum length of %li but found %li",
      array_maxlength, *array_length);
    return reflect_failure(target->schema);
  }

allocate_array:
  struct reflect* element = vector_get(target->schema->child, 0);
  u64 array_typesize = reflect_typesize(element);

  struct array array = array_init(array_typesize, *array_length, target->allocator);
  array.length = *array_length;

decode_array:
  for (u64 i = 0; i < array.length; i++) {
    element->index = i;
    struct object element_object = {
      .schema = element,
      .address = array.data + (i * array_typesize),
      .allocator = target->allocator
    };
    binary_decode(source, &element_object);
    if (error.occurred)
      return;
  }

validate_array:
  reflect_validate(target->schema, &array);
  if (error.occurred)
    return reflect_failure(target->schema);

write_target:
  memcpy(target->address, &array, sizeof(struct array));
}
