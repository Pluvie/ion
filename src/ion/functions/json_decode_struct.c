static inline void json_decode_struct (
    struct io* source,
    struct object* target
)
{
  char* character;

  bool field_is_string = false;
  u64 field_index = 0;
  struct reflect* field_reflection = NULL;
  struct object field_object = { 0 };
  struct string field_name = { 0 };

object_begin:
  json_parse_spaces(source);
  if (error.occurred)
    return;

  character = io_read(source, sizeof(char));
  if (error.occurred)
    return;

  if (*character != '{') {
    fail("expected `{` to begin object");
    error_add_io_extraction(source);
    return;
  }

next_field:
  json_parse_spaces(source);
  if (error.occurred)
    return;

  character = io_read(source, sizeof(char));
  if (error.occurred)
    return;

check_empty_object:
  if (*character == '}') {

    if (field_index > 0) {
      /* Moves back the cursor to the comma before the spaces, if any, to print the
       * correct cursor caret helper, using the `error_add_io_extraction` function. */
      source->cursor -= source->read_amount;
      fail("trailing comma before object end");
      error_add_io_extraction(source);
    }

    goto terminate;
  }

parse_field:
  /* Moves back the cursor as the character was not '}' and thus not an empty object. */
  source->cursor -= source->read_amount;

  field_is_string = json_parse_string(source, (u64*) &(field_name.length));
  if (error.occurred)
    return;

  if (!field_is_string) {
    fail("expected a string as object key");
    error_add_io_extraction(source);
    return;
  }

read_field:
  if (target == NULL) {
    field_reflection = NULL;
    goto check_semicolon;
  }

  source->cursor -= field_name.length;
  field_name.content = memory_alloc(target->allocator, field_name.length);
  field_name.content = io_read(source, field_name.length);
  if (error.occurred)
    return;

  for vector_each(target->reflection->child, struct reflect*, f) {
    /* Field name equality must be done removing the `"` surrounding `field_name`.*/
    if (strneq(f->name, field_name.content + 1, field_name.length - 2)) {
      field_reflection = f;
      goto check_semicolon;
    }
  }

  field_reflection = NULL;

check_semicolon:
  json_parse_spaces(source);
  if (error.occurred)
    return;

  character = io_read(source, sizeof(char));
  if (error.occurred)
    return;

  if (*character != ':') {
    fail("expected a `:` after the field name");
    error_add_io_extraction(source);
    return;
  }

  json_parse_spaces(source);
  if (error.occurred)
    return;

parse_value:
  if (field_reflection != NULL) {
    field_object.name = field_reflection->name;
    field_object.reflection = field_reflection;
    field_object.address = target->address + field_reflection->offset;
    field_object.allocator = target->allocator;
  }

  json_decode(source, field_reflection != NULL ? &field_object : NULL);
  if (error.occurred)
    return;

check_comma:
  json_parse_spaces(source);
  if (error.occurred)
    return;

  character = io_read(source, sizeof(char));
  if (error.occurred)
    return;

  switch (*character) {
  case '}':
    goto terminate;

  case ',':
    field_index++;
    goto next_field;

  default:
    fail("expected comma or object end after field value");
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
