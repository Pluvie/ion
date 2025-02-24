static inline void binary_decode_array (
    struct io* source,
    struct object* target
)
{
read_length:
  u64 array_length; io_read(source, &array_length, sizeof(u64));
  if (error.occurred)
    return error_add_reflection_path(target->reflection);

check_minlength:
  u64 array_minlength = target->reflection->bounds[0];
  if (array_minlength > 0 && array_length < array_minlength) {
    fail("array required minimum length of %li but found %li",
      array_minlength, array_length);
    return error_add_reflection_path(target->reflection);
  }

check_maxlength:
  u64 array_maxlength = target->reflection->bounds[1];
  if (array_maxlength > 0 && array_length > array_maxlength) {
    fail("array required maximum length of %li but found %li",
      array_maxlength, array_length);
    return error_add_reflection_path(target->reflection);
  }

allocate_array:
  struct reflect* element_reflection = vector_get(target->reflection->child, 0);
  u64 element_typesize = reflect_typesize(element_reflection);

  struct array array = array_init(element_typesize, array_length, target->allocator);
  array.length = array_length;

decode_array:
  for (u64 i = 0; i < array.length; i++) {
    element_reflection->index = i;
    struct object element = {
      .reflection = element_reflection,
      .address = array.data + (i * element_typesize),
      .allocator = target->allocator
    };
    binary_decode(source, &element);
    if (error.occurred)
      return;
  }

validate_array:
  reflect_validate(target->reflection, &array);
  if (error.occurred)
    return error_add_reflection_path(target->reflection);

write_target:
  memcpy(target->address, &array, sizeof(struct array));
}
