static inline struct map* csv_decode_headers (
    struct io* input,
    struct vector* fields,
    struct memory* allocator,
    struct csv_properties csv
)
{
  struct map* headers = NULL;

  struct buffer buffer = { 0 };
  u64 max_position = U64_MAX;

  char* header_row = NULL;
  char character;

  u64 position = 0;
  u64 newline_position = 0;
  u32 separators_count = 0;

check_empty:
  bool is_empty = io_exhausted(input);
  if (error.occurred)
    goto terminate;

  if (is_empty) {
    fail("csv is empty");
    goto terminate;
  }

peek_headers:
  header_row = io_peek_window(input, &buffer, &max_position);
  if (error.occurred)
    goto terminate;

find_newline:
  character = header_row[position];

  if (character == '\n') {
    newline_position = position;
    goto split_headers;
  }

  if (character == csv.separator)
    separators_count++;

  position++;
  if (position >= max_position)
    goto terminate;

  if (position < buffer.capacity)
    goto find_newline;
  else
    goto peek_headers;

split_headers:
  if (newline_position == 0) {
    fail("expected a csv with at least one column");
    goto terminate;
  }

  if (separators_count != csv.columns_count - 1) {
    fail("expected a csv with %i columns, but found only %i separators `%c`",
      csv.columns_count, separators_count, csv.separator);
    goto terminate;
  }

  headers = map_allocate(
    sizeof(u64), sizeof(struct csv_header), csv.columns_count, allocator);

  char* header = NULL;
  u64 header_begin = 0;
  u64 header_end = 0;
  u64 header_index = 0;
  i32 header_length = 0;
  u64 cursor = 0;

read_header:
  if (header_row[cursor] != '\n' && header_row[cursor] != csv.separator) {
    cursor++;
    goto read_header;
  }

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

    header_length = (i32) (header_end - header_begin) - 2;
    header = memory_alloc_zero(allocator, header_length + 1);
    snprintf(header, header_length + 1, "%s", header_row + header_begin + 1);

  } else {
    header_length = (i32) (header_end - header_begin);
    header = memory_alloc_zero(allocator, header_length + 1);
    snprintf(header, header_length + 1, "%s", header_row + header_begin);
  }

  for vector_each(fields, struct reflect*, field) {
    if (!streq(field->name, header))
      continue;

    map_set(headers, &header_index, &(struct csv_header) {
      .name = header,
      .index = header_index,
      .target = &(struct object) {
        .name = field->name,
        .reflection = field,
        .allocator = allocator
       },
    });
    break;
  }
  
  header_begin = header_end + 1;
  header_index++;
  cursor++;

  if (cursor > newline_position)
    goto terminate;

  goto read_header;

incorrect_wrapper:
  fail("expected field to be wrapped with `%c`", csv.wrapper);
  error_add_io_extraction(input);
  headers = NULL;
  goto terminate;
  
terminate:
  buffer_release(&buffer);
  return headers;
}
