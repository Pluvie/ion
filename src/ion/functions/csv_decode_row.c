static inline void csv_decode_row (
    struct io* input,
    struct object* target,
    struct map* headers,
    struct csv_properties csv
)
{
  struct buffer buffer = { 0 };
  u64 max_position = U64_MAX;

  char* row = NULL;
  char character;

  u64 position = 0;
  u64 newline_position = 0;
  u32 separators_count = 0;

peek_row:
  row = io_peek_window(input, &buffer, &max_position);
  if (error.occurred)
    goto terminate;

count_separators:
  character = row[position];

  if (separators_count == csv.columns_count - 1 && character == '\n') {
    newline_position = position;
    goto split_row;
  }

  if (character == csv.separator)
    separators_count++;

  position++;
  if (position >= max_position) {
    fail("unable to decode csv row: end of input reached");
    goto terminate;
  }

  if (position < buffer.capacity)
    goto count_separators;
  else
    goto peek_row;

split_row:
  char* field = NULL;
  u64 field_begin = 0;
  u64 field_end = 0;
  u64 field_index = 0;
  i32 field_length = 0;
  u64 cursor = 0;

read_field:
  if (row[cursor] != csv.separator) {
    cursor++;
    goto read_field;
  }

  field_end = cursor;

  if (csv.wrapper != 0) {
    if (row[field_begin] != csv.wrapper) {
      input->cursor = field_begin + 1;
      goto incorrect_wrapper;
    }

    if (row[field_end - 1] != csv.wrapper) {
      input->cursor = field_end - 1;
      goto incorrect_wrapper;
    }

    field_length = (i32) (field_end - field_begin) - 2;
    field = memory_alloc_zero(target->allocator, field_length + 1);
    snprintf(field, field_length + 1, "%s", row + field_begin + 1);

  } else {
    field_length = (i32) (field_end - field_begin);
    field = memory_alloc_zero(target->allocator, field_length + 1);
    snprintf(field, field_length + 1, "%s", row + field_begin);
  }

  for vector_each(fields, struct reflect*, field) {
    if (!streq(field->name, field))
      continue;

    map_set(fields, &field_index, &(struct csv_field) {
      .name = field,
      .index = field_index,
      .target = &(struct object) {
        .name = field->name,
        .reflection = field,
        .allocator = allocator
       },
    });
    break;
  }
  
  field_begin = field_end + 1;
  field_index++;
  cursor++;

  if (cursor > newline_position)
    goto advance_io_cursor;

  goto read_field;

terminate:
  buffer_release(&buffer);
  return;
}
