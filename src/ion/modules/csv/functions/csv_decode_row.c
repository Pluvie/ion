static inline void csv_decode_row (
    struct io* source,
    struct object* target,
    struct map* headers,
    struct csv_properties csv
)
{
  u64 initial_cursor_position = source->cursor;
  u64 position = 0;
  u64 newline_position = 0;
  u64 peek_window = 1024;

  char* row = NULL;
  char character;

check_empty_source:
  bool is_empty = io_exhausted(source);
  if (error.occurred)
    return;

  if (is_empty) {
    fail("csv is empty");
    return;
  }

read_source:
  row = io_read(source, peek_window);
  if (error.occurred)
    return;

find_newline:
  character = row[position];

  if (character == '\n') {
    newline_position = position;
    goto check_newline_position;
  }

next_character:
  position++;

  if (position < source->length)
    goto find_newline;

  peek_window *= 2;
  goto read_source;

check_newline_position:
  if (newline_position == 0) {
    fail("expected a csv row with at least one column");
    return;
  }

  source->cursor = initial_cursor_position + newline_position + 1;

split_row:
  struct string row_string = { row, (i32) newline_position };
  struct array* columns = string_split(
    row_string, target->allocator, csv.separator, csv.wrapper);

check_columns:
  if (headers->length != csv.columns_count)
    goto read_source;

decode_columns:
  for array_each_with_index(columns, column_index, struct string*, column) {
    struct csv_header* column_header = map_get(headers, &column_index);
    struct object* column_object = column_header->target;
    column_object->address = target->address + column_object->reflection->offset;

    csv_decode_column(column, column_object);
    if (error.occurred)
      return;
  }

validate:
  reflect_validate(target->reflection, target->address);
  if (error.occurred) {
    error_add_io_extraction(source);
    error_add_reflection_path(target->reflection);
    return;
  }
}
