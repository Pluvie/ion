static inline struct map* csv_decode_headers (
    struct io* input,
    struct vector* fields,
    struct memory* allocator,
    struct csv_properties csv
)
{
  struct map* headers_mapping = NULL;
  struct array* headers = NULL;

  struct buffer buffer = { 0 };
  u64 max_position = U64_MAX;

  char* header_row = NULL;
  char character;

  u64 position = 0;
  u64 newline_position = 0;
  u32 separators_count = 0;

check_empty_input:
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
  if (position >= max_position) {
    fail("unable to decode csv headers: end of input reached");
    goto terminate;
  }

check_newline_position:
  if (position < buffer.capacity)
    goto find_newline;
  else
    goto peek_headers;

  if (newline_position == 0) {
    fail("expected a csv with at least one header column");
    goto terminate;
  }

  if (separators_count != csv.columns_count - 1) {
    fail("expected a csv with %i columns, but found only %i separators `%c`",
      csv.columns_count, separators_count, csv.separator);
    goto terminate;
  }

split_headers:
  u64 cursor = 0;
  bool incorrect_wrapper = false;

  headers_mapping = map_allocate(
    sizeof(u64), sizeof(struct csv_header), csv.columns_count, allocator);
  headers = string_split(
    (struct string) { header_row, (i32) newline_position }, csv.separator, allocator);

  for array_each_with_index(headers, header_index, struct string*, header) {

    if (csv.wrapper != '\0') {
      if (header->content[0] != csv.wrapper) {
        input->cursor = cursor;
        incorrect_wrapper = true;
      }

      if (header->content[header->length - 1] != csv.wrapper) {
        input->cursor = cursor + header->length;
        incorrect_wrapper = true;
      }
      
      if (incorrect_wrapper) {
        fail("expected field to be wrapped with `%c`", csv.wrapper);
        error_add_io_extraction(input);
        return NULL;
      }
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

    cursor += header->length;
  }
  
advance_io_cursor:
  io_read(input, NULL, newline_position + 1);
  if (error.occurred)
    return NULL;
  
terminate:
  buffer_release(&buffer);
  return headers_mapping;
}
