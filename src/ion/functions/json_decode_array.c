static inline void json_decode_array (
    struct io* source,
    struct object* target
)
{
  u64 amount_read = 0;
  char character;

  struct reflect* element_reflection = NULL;
  struct object element_object = { 0 };
  u64 element_index = 0;
  u64 element_typesize = 0;

  struct array array;
  u64 array_minlength = 0;
  u64 array_maxlength = 0;
  void* empty_element = NULL;

  if (target != NULL) {
    element_reflection = vector_get(target->reflection->child, 0);
    element_typesize = reflect_typesize(element_reflection);
    empty_element = memory_alloc_zero(target->allocator, element_typesize);
    array = array_init(element_typesize, 0, target->allocator);
    array_minlength = target->reflection->bounds[0];
    array_maxlength = target->reflection->bounds[1];
  }

array_begin:
  amount_read = json_parse_spaces(source);
  if (amount_read > 0) {
    io_read(source, NULL, amount_read);
    if (error.occurred)
      return;
  }

  io_read(source, &character, sizeof(char));
  if (error.occurred)
    return;

  if (character != '[') {
    fail("expected `[` to begin array");
    error_add_io_extraction(source);
    return;
  }

next_element:
  amount_read = json_parse_spaces(source);
  if (error.occurred)
    return;

  if (amount_read > 0) {
    io_read(source, NULL, amount_read);
    if (error.occurred)
      return;
  }

  io_peek(source, &character, sizeof(char));
  if (error.occurred)
    return;

check_empty_array:
  if (character == ']') {

    if (element_index > 0) {
      /* Moves back the cursor to the comma before the spaces, if any, to print the
       * correct cursor caret helper, using the `error_add_io_extraction` function. */
      source->cursor -= amount_read;
      fail("trailing comma before array end");
      error_add_io_extraction(source);
    }

    io_read(source, NULL, sizeof(char));
    if (error.occurred)
      return;

    goto terminate;
  }

parse_value:
  if (element_reflection != NULL) {
    element_reflection->index = element_index;
    element_object.name = element_reflection->name;
    element_object.reflection = element_reflection;
    element_object.address = array_push(&array, empty_element);
    element_object.allocator = target->allocator;
  }

  json_decode(source, element_reflection != NULL ? &element_object : NULL);
  if (error.occurred)
    return;

check_comma:
  amount_read = json_parse_spaces(source);
  if (amount_read > 0) {
    io_read(source, NULL, amount_read);
    if (error.occurred)
      return;
  }

  io_read(source, &character, sizeof(char));
  if (error.occurred)
    return;

  switch (character) {
  case ']':
    goto terminate;

  case ',':
    element_index++;
    if (array_maxlength > 0 && element_index >= array_maxlength) {
      fail("array required maximum length of %li", array_maxlength);
      error_add_io_extraction(source);
      return error_add_reflection_path(target->reflection);
    }

    goto next_element;

  default:
    fail("expected comma or array end after value");
    error_add_io_extraction(source);
    return;
  }

terminate:
  if (target == NULL)
    return;

  if (array_minlength > 0 && array.length < array_minlength) {
    fail("array required minimum length of %li", array_minlength);
    error_add_io_extraction(source);
    return error_add_reflection_path(target->reflection);
  }

  reflect_validate(target->reflection, &array);
  if (error.occurred)
    return error_add_reflection_path(target->reflection);

  memcpy(target->address, &array, sizeof(struct array));
}
