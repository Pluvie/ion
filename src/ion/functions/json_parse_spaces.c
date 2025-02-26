static inline u64 json_parse_spaces (
    struct io* input
)
{
  char character;
  u64 position = 0;

  struct buffer buffer = { 0 };
  u64 max_position = U64_MAX;

  char* spaces = NULL;

peek_spaces:
  spaces = io_peek_window(input, &buffer, &max_position);
  if (error.occurred) {
    position = 0;
    goto terminate;
  }

read_character:
  character = spaces[position];

  if (!isspace(character))
    goto terminate;

next_character:
  position++;
  if (position >= max_position) {
    position = 0;
    goto terminate;
  }

  if (position < buffer.capacity)
    goto read_character;
  else
    goto peek_spaces;

terminate:
  buffer_release(&buffer);
  return position;
}
