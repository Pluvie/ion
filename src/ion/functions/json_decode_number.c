static inline void json_decode_number (
    struct io* input,
    struct io* output,
    struct protocol* json
)
{
  json_decode_spaces(input, output, json);

  struct reflect* schema = json->schema;
  struct failure parse_error = { 0 };
  struct sci_notation number = json_parse_number(input, &parse_error);

  if (parse_error.occurred) {
    failure(&(json->error), "[%s] invalid JSON, unable to parse number: %s",
      schema->name, parse_error.message);
    return;
  }

  u32 type_size = type_sizes[schema->type];
  byte number_bytes[type_size];
  struct failure convert_error = { 0 };

  if (!sci_notation_convert(number_bytes, schema->type, &number, &convert_error)) {
    failure(&(json->error), "[%s] %s", schema->name, convert_error.message);
    return;
  }

  u64 written_bytes = io_write(output, number_bytes, type_size);
  if (written_bytes == 0) {
    failure(&(json->error), "[%s] unable to write %i bytes to output: data length "\
      "is %li bytes, but cursor already at %li",
      schema->name, type_size, output->length, output->cursor);
    return;
  }

  json_decode_spaces(input, output, json);
}
