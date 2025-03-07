static inline struct array* csv_parse_row (
    struct io* source,
    struct memory* allocator,
    struct csv_properties csv
)
{
  struct array* fields = array_allocate(sizeof(struct string), 0, allocator);
  bool last_field = false;

  struct string field = { 0 };
  u64 field_begin = 0;
  u64 row_length = 0;

  char* character;

  io_cursor_save(source);

next_field:
  field_begin = source->cursor;

  character = io_read(source, sizeof(char));
  if (error.occurred)
    return NULL;

  if (*character == csv.wrapper)
    goto parse_wrapped;
  else
    goto parse_unwrapped;


  /* Parsing an unwrapped field: shall end when the separator is encountered, or when
   * a newline is encountered and the fields count is equal to the expected quantity.
   * If a newline is encountered and the fields count is below the expected quantity,
   * the parsing continues, otherwise the function shall fail. */
parse_unwrapped:
  character = io_read(source, sizeof(char));
  if (error.occurred)
    return NULL;

  if (*character == csv.separator)
    goto push_field;

  if (*character == '\n') {
    if (fields->length < csv.columns_count - 1)
      goto parse_unwrapped;

    last_field = true;
    goto push_field;
  }

  goto parse_unwrapped;


  /* Parsing an wrapped field: shall end when the separator or newline is encountered,
   * but only if encountered after the wrapper char. Shall fail if the fields count is
   * not equal to the expected quantity. */
parse_wrapped:
  character = io_read(source, sizeof(char));
  if (error.occurred)
    return NULL;

  if (*character == csv.wrapper)
    goto check_wrapper_terminator;

  goto parse_wrapped;

check_wrapper_terminator:
  character = io_read(source, sizeof(char));
  if (error.occurred)
    return NULL;

  if (*character == csv.wrapper)
    goto parse_wrapped;

  if (*character == '\n') {
    last_field = true;
    goto push_field;
  }

  if (*character == csv.separator)
    goto push_field;

  fail("expected separator `%c`, or newline, after wrapper `%c`",
    csv.separator, csv.wrapper);
  error_add_io_extraction(source);
  return NULL;


  /* Pushes the field in the fields array. If this is the last field, terminates,
   * otherwise keeps parsing. */
push_field:
  field.length = source->cursor - field_begin;
  source->cursor = field_begin;

  char* field_content = io_read(source, field.length);
  if (error.occurred)
    return NULL;

  field.content = memory_alloc(allocator, field.length);
  memcpy(field.content, field_content, field.length);
  field.content[field.length - 1] = '\0';

  row_length += field.length;
  field.length--;

  array_push(fields, &field);
  memzero(&field, sizeof(struct string));

  if (last_field)
    goto terminate;

  if (fields->length >= csv.columns_count) {
    fail("expected newline but found more than the specified %i columns count", csv.columns_count);
    error_add_io_extraction(source);
    return NULL;
  }

  goto next_field;

terminate:
  io_cursor_restore(source);
  io_read(source, row_length);
  if (error.occurred)
    return NULL;

  return fields;
}
