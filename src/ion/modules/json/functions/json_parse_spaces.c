static inline bool json_parse_spaces (
    struct io* source
)
{
  u64 initial_cursor_position = source->cursor;
  u64 position = 0;
  u64 peek_window = 1024;

  char* spaces = NULL;
  char character;

read_source:
  spaces = io_read(source, peek_window);
  if (error.occurred)
    return false;

read_character:
  character = spaces[position];

  if (!isspace(character))
    goto terminate;

next_character:
  position++;

  if (position < source->length)
    goto read_character;

  peek_window *= 2;
  goto read_source;

terminate:
  source->cursor = initial_cursor_position + position;
  return position > 0;
}
