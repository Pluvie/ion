static inline void json_decode_sequence (
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
  u64 sequence_length = 0;

  if (target != NULL) {
    element_reflection = vector_get(target->reflection->child, 0);
    element_typesize = reflect_typesize(element_reflection);
    sequence_length = target->reflection->bounds[0];
  }

sequence_begin:
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
    fail("expected `[` to begin a sequence");
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

check_empty_sequence:
  if (character == ']') {

    if (element_index > 0) {
      /* Moves back the cursor to the comma before the spaces, if any, to print the
       * correct cursor caret helper, using the `error_add_io_extraction` function. */
      source->cursor -= amount_read;
      fail("trailing comma before sequence end");
      error_add_io_extraction(source);
    }

    io_read(source, NULL, sizeof(char));
    if (error.occurred)
      return;

    goto terminate;
  }

parse_value:
  /* Ignores all elements that are over the sequence length. */
  if (element_index >= sequence_length)
    element_reflection = NULL;

  if (element_reflection != NULL) {
    element_reflection->index = element_index;
    element_object.name = element_reflection->name;
    element_object.reflection = element_reflection;
    element_object.address = target->address + (element_index * element_typesize);
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
    goto next_element;

  default:
    fail("expected comma or array end after value");
    error_add_io_extraction(source);
    return;
  }

terminate:
  if (target == NULL)
    return;

  reflect_validate(target->reflection, target->address);
  if (error.occurred)
    return error_add_reflection_path(target->reflection);
}
