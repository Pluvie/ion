static inline void json_decode_struct (
    struct io* source,
    struct object* target
)
{
  u64 amount_read = 0;
  char character;

  u64 field_index = 0;
  struct reflect* field_reflection = NULL;
  struct object field_object = { 0 };

  struct memory allocator = memory_init(0);
  struct string field_name = { 0 };

object_begin:
  amount_read = json_parse_spaces(source);
  if (amount_read > 0) {
    io_read(source, NULL, amount_read);
    if (error.occurred)
      return;
  }

  io_read(source, &character, sizeof(char));
  if (error.occurred)
    return;

  if (character != '{') {
    fail("expected `{` to begin object");
    return;
  }

next_field:
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

  if (field_index == 0 && character == '}')
    return;

  amount_read = json_parse_string(source);
  if (error.occurred)
    return;

  if (amount_read == 0) {
    fail("expected a string as object key");
    return;
  }

  field_name.content = memory_alloc(&allocator, amount_read);
  field_name.length = amount_read;
  io_read(source, field_name.content, field_name.length);
  if (error.occurred)
    return;

  if (target != NULL) {
    for vector_each(target->reflection->child, struct reflect*, field_reflection) {
      /* Field name equality must be done removing the `"` surrounding `field_name`.*/
      if (strneq(field_reflection->name, field_name.content + 1, field_name.length - 2))
        goto check_semicolon;

      field_reflection++;
    }
  }

  field_reflection = NULL;

  if (field_reflection != NULL) {
    field_object.name = field_reflection->name;
    field_object.reflection = field_reflection;
    field_object.address = target->address + field_reflection->offset;
    field_object.allocator = target->allocator;
  }

check_semicolon:
  amount_read = json_parse_spaces(source);
  if (amount_read > 0) {
    io_read(source, NULL, amount_read);
    if (error.occurred)
      return;
  }

  io_read(source, &character, sizeof(char));
  if (error.occurred)
    return;

  if (character != ':') {
    fail("[%.*s] expected a `:` after the field name",
      (i32) field_name.length, field_name.content);
    return;
  }

  amount_read = json_parse_spaces(source);
  if (amount_read > 0) {
    io_read(source, NULL, amount_read);
    if (error.occurred)
      return;
  }

parse_value:
  json_decode(source, field_reflection != NULL ? &field_object : NULL);
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
  case '}':
    return;

  case ',':
    field_index++;
    goto next_field;

  default:
    fail("unexpected character `%c`: expected comma or object end after field value",
      character);
    return;
  }
}
