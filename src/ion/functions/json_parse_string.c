static inline u64 json_parse_string (
    struct io* input
)
{
  char character;
  bool escaped = false;
  u64 position = 0;

  struct buffer buffer = { 0 };
  u64 max_position = U64_MAX;

  char* string = NULL;

peek_string:
  string = io_peek_window(input, &buffer, &max_position);
  if (error.occurred) {
    position = 0;
    goto terminate;
  }

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
  if (position >= max_position) {
    position = 0;
    goto terminate;
  }

  if (position < buffer.capacity)
    goto read_character;
  else
    goto peek_string;

terminate:
  buffer_release(&buffer);
  return position;
}
