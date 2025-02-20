static inline void json_decode_struct (
    struct io* source,
    struct object* target
)
{
  u64 amount_read = 0;
  char character;

  u64 fields_count = reflection->bounds[1];
  struct reflect* field = NULL;
  struct object field_object = { 0 };
  struct object* target_field = NULL;

object_begin:
  amount_read = json_parse_spaces(source);
  if (amount_read > 0) {
    io_read(source, memory_alloc(target->allocator, amount_read), amount_read);
    if (error.occurred)
      return;
  }

  io_peek(input, &character, sizeof(char));
  if (error.occurred)
    return;

  if (character != '{') {
    fail("expected `{` to begin object");
    return;
  }

next_field:
  amount_read = json_parse_spaces(source);
  if (amount_read > 0) {
    io_read(source, memory_alloc(target->allocator, amount_read), amount_read);
    if (error.occurred)
      return;
  }

  io_peek(input, &character, sizeof(char));
  if (error.occurred)
    return;

  if (character == '}')
    goto terminate;

  amount_read = json_parse_string(source);
  if (error.occurred)
    return;

  if (amount_read == 0) {
    fail("expected a string as object key");
    return;
  }

  field = target->reflection->nodes;
  for (u64 i = 0; i < fields_count; i++) {
    /* Field name equality must be done removing the `"` surrounding `field_name`.*/
    if (strneq(field->name, field_name.content + 1, field_name.length - 2))
      goto check_semicolon;

    field++;
  }

  /* Here need to parse the field value and ignore it since it does not match any
   * field in the reflection. */
  field = NULL;
  target_field = NULL;

  if (field != NULL) {
    field_object = {
      .name = field->name,
      .reflection = field,
      .address = target->address + field->offset,
      .allocator = target->allocator
    };
    target_field = &field_object;
  }

check_semicolon:
  amount_read = json_parse_spaces(source);
  if (amount_read > 0) {
    io_read(source, memory_alloc(target->allocator, amount_read), amount_read);
    if (error.occurred)
      return;
  }

  io_read(input, &character, sizeof(char));
  if (error.occurred)
    return;

  if (character != ':') {
    fail("[%s] expected a `:` after the field name", field->name);
    return;
  }

  amount_read = json_parse_spaces(source);
  if (amount_read > 0) {
    io_read(source, memory_alloc(target->allocator, amount_read), amount_read);
    if (error.occurred)
      return;
  }

parse_value:
  io_peek(input, &character, sizeof(char));
  if (error.occurred)
    return;

  switch (character) {
  case '{':
    if (field->type != STRUCT) {
      fail("[%s] field of type %s but found an object",
        field->name, type_names[field->type]);
      return;
    }

    json_decode(
  }






















next_field:
  json_decode_spaces(input, output, json);
  field_name = json_parse_string(input, &(json->error));

  if (field_name.length == 0)
    goto object_end;

  field = reflection->nodes;
  for (u64 i = 0; i < fields_count; i++) {
    /* Field name equality must be done removing the `"` surrounding `field_name`.*/
    if (strneq(field->name, field_name.content + 1, field_name.length - 2))
      goto check_semicolon;

    field++;
  }

  failure(&(json->error), "[%s] unrecognized field `%.*s`",
    reflection->name, (i32) field_name.length, field_name.content);
  return;

decode_field:
  json->reflection = field;
  output->cursor = output_initial_cursor + field->offset;
  json_decode(input, output, json);

  if (json->error.occurred)
    return;

comma_separator:
  json_decode_spaces(input, output, json);
  comma = io_peek(input, sizeof(char));
  if (comma == NULL) {
    failure(&(json->error), "[%s] expected a `,` after the field value but found EOF",
      reflection->name);
    return;
  }

  if (*comma == ',') {
    io_read(input, sizeof(char));
    goto next_field;
  }

object_end:
  curly_close = io_read(input, sizeof(char));
  if (curly_close == NULL || *curly_close != '}') {
    failure(&(json->error), "[%s] expected a field or `}` to end object",
      reflection->name);
    return;
  }

  json->reflection = schema;
  output->cursor = output_initial_cursor + struct_typesize;
}
