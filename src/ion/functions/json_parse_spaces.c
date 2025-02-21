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
  spaces = json_parser_peek(input, &buffer, &max_position);
  if (error.occurred)
    return 0;

read_character:
  character = spaces[position];

  if (!isspace(character)) {
    buffer_release(&buffer);
    return position;
  }

next_character:
  position++;
  if (position >= max_position) {
    fail("[%li] expected a space but found EOF", input->cursor);
    return 0;
  }

  if (position < buffer.capacity)
    goto read_character;
  else
    goto peek_spaces;

  return 0;
}
