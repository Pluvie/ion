static inline struct array* csv_parse_row (
    struct io* source,
    struct memory* allocator,
    struct csv_properties csv
)
{
  struct array* fields = array_allocate(sizeof(struct string), 0, allocator);
  bool last_field = false;

  char* character;

next_field:
  io_cursor_save(source);

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
  u64 field_length = source->cursor - source->saved_cursor;
  io_cursor_restore(source);
  char* field_content = io_read(source, field_length);
  if (error.occurred)
    return NULL;

  struct string field = {
    .content = memory_alloc(allocator, field_length),
    .length = field_length
  };
  memcpy(field.content, field_content, field_length - 1);
  field.content[field_length - 1] = '\0';
  array_push(fields, &field);

  if (last_field)
    goto terminate;

  if (fields->length + 1 > csv.columns_count) {
    fail("expected newline but found more than the specified %i columns count", csv.columns_count);
    error_add_io_extraction(source);
    return NULL;
  }

  goto next_field;

terminate:
  return fields;
}
