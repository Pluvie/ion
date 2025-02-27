static inline bool json_parse_string (
    struct io* source,
    u64* string_length
)
{
  u64 initial_cursor_position = source->cursor;
  u64 position = 0;
  u64 peek_window = 1024;

  char* string = NULL;
  char character;
  bool escaped = false;

read_source:
  string = io_read(source, peek_window);
  if (error.occurred)
    return false;

read_character:
  character = string[position];

  if (escaped) {
    escaped = false;
    goto next_character;
  }

  if (character == 92) {
    escaped = true;
    goto next_character;
  }

  if (character == '"' && position > 0) {
    position++;
    goto terminate;
  }

  if (unlikely(character != '"' && position == 0)) {
    position = 0;
    goto terminate;
  }

next_character:
  position++;

  if (position < source->length)
    goto read_character;

  peek_window *= 2;
  goto read_source;

terminate:
  source->cursor = initial_cursor_position + position;

  if (string_length != NULL)
    *string_length = position;

  return position > 0;
}
