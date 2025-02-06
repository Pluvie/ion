static inline void json_decode_struct (
    struct io* input,
    struct io* output,
    struct protocol* json
)
{
  struct reflect* reflection = json->schema;
  u64 output_initial_cursor = output->cursor;
  u64 struct_typesize = reflection->bounds[0];
  u64 fields_count = reflection->bounds[1];

  char* curly_open;
  char* curly_close;
  char* semicolon;
  char* comma;

  struct string field_name;
  struct reflect* field = reflection->nodes;

object_begin:
  json_decode_spaces(input, output, json);

  curly_open = io_read(input, sizeof(char));
  if (curly_open == NULL || *curly_open != '{') {
    failure(&(json->error), "[%s] expected `{` to begin object",
      reflection->name);
    return;
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

check_semicolon:
  json_decode_spaces(input, output, json);
  semicolon = io_peek(input, sizeof(char));
  if (semicolon == NULL || *semicolon != ':') {
    failure(&(json->error), "[%s] expected a `:` after the field name",
      reflection->name);
    return;
  }
  io_read(input, sizeof(char));

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
