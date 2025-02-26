static inline void* csv_decode_headers (
    struct io* input,
    struct memory* allocator,
    struct csv_properties csv
)
{
  struct vector* headers = NULL;

  struct buffer buffer = { 0 };
  u64 max_position = U64_MAX;

  char* header_row = NULL;
  char character;

  u64 position = 0;
  u64 newline_position = 0;
  u32 separators_count = 0;

peek_headers:
  header_row = io_peek_window(input, &buffer, &max_position);
  if (error.occurred) {
    header_row = NULL;
    goto terminate;
  }

find_newline:
  character = header_row[position];

  if (character == '\n') {
    newline_position = position;
    goto split_headers;
  }

  if (character == csv.separator)
    separators_count++;

  position++;
  if (position >= max_position) {
    headers = NULL;
    goto terminate;
  }

  if (position < buffer.capacity)
    goto find_newline;
  else
    goto peek_headers;

split_headers:
  if (newline_position == 0) {
    fail("expected a csv with at least one column");
    headers = NULL;
    goto terminate;
  }

  if (separators_count != csv.columns_count - 1) {
    fail("expected a csv with %i columns, but found only %i separators `%c`",
      csv.columns_count, separators_count, csv.separator);
    headers = NULL;
    goto terminate;
  }

  headers = vector_allocate(sizeof(char[128]), csv.columns_count, allocator);
  char header[128] = { 0 };
  u64 header_begin = 0;
  u64 header_end = 0;
  u32 header_index = 0;

  for (u64 cursor = 0; cursor <= newline_position; cursor++) {
    if (header_row[cursor] != '\n' && header_row[cursor] != csv.separator)
      continue;

    header_end = cursor;

    if (csv.wrapper != 0) {
      if (header_row[header_begin] != csv.wrapper) {
        input->cursor = header_begin + 1;
        goto incorrect_wrapper;
      }

      if (header_row[header_end - 1] != csv.wrapper) {
        input->cursor = header_end - 1;
        goto incorrect_wrapper;
      }

      snprintf(header, sizeof(header), "%.*s",
        (i32) (header_end - header_begin) - 2, header_row + header_begin + 1);

    } else {
      snprintf(header, sizeof(header), "%.*s",
        (i32) (header_end - header_begin), header_row + header_begin);
    }

    vector_set(headers, header_index, header);
    header_begin = header_end + 1;
    header_index++;
  }
  
terminate:
  buffer_release(&buffer);
  return headers;

incorrect_wrapper:
  fail("expected field to be wrapped with `%c`", csv.wrapper);
  error_add_io_extraction(input);
  headers = NULL;
  goto terminate;
}
