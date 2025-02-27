static inline struct map* csv_decode_headers (
    struct io* source,
    struct vector* fields,
    struct memory* allocator,
    struct csv_properties csv
)
{
  u64 initial_cursor_position = source->cursor;
  u64 position = 0;
  u64 newline_position = 0;
  u64 peek_window = 1024;

  char* header = NULL;
  char character;

check_empty_source:
  bool is_empty = io_exhausted(source);
  if (error.occurred)
    return NULL;

  if (is_empty) {
    fail("csv is empty");
    return NULL;
  }

read_source:
  header = io_read(source, peek_window);
  if (error.occurred)
    return NULL;

find_newline:
  character = header[position];

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
    fail("expected a csv header with at least one column");
    return NULL;
  }

  source->cursor = initial_cursor_position + newline_position + 1;

split_headers:
  struct map* headers_mapping = map_allocate(
    sizeof(u64), sizeof(struct csv_header),
    csv.columns_count, allocator);

  struct string header_string = { header, (i32) newline_position };
  struct array* headers = string_split(
    header_string, allocator, csv.separator, csv.wrapper);

check_columns:
  if (headers->length != csv.columns_count) {
    fail("expected a csv with %i columns, but found only %li separators `%c`",
      csv.columns_count, headers->length - 1, csv.separator);
    return NULL;
  }

map_headers:
  for array_each_with_index(headers, header_index, struct string*, header) {
    if (csv.wrapper != '\0') {
      header->content += 1;
      header->length -= 2;
    }

    for vector_each(fields, struct reflect*, field) {
      if (!strneq(field->name, header->content, header->length))
        continue;

      map_set(headers_mapping, &header_index, &(struct csv_header) {
        .index = header_index,
        .name = header,
        .target = &(struct object) {
          .name = field->name,
          .reflection = field,
          .allocator = allocator
         },
      });

      break;
    }
  }

  return headers_mapping;
}
