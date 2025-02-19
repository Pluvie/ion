static inline u64 json_parse_string (
    struct io* input
)
{
  char* string = NULL;

  u64 position = 0;
  u64 max_position = U64_MAX;

  bool escaped = false;
  char character;

  u64 peek_size = 256;
  struct buffer buffer = { 0 };

initialize:
  switch (input->channel) {
  case IO_CHANNEL_MEM:
    max_position = input->length - input->cursor;

    string = io_peek(input, NULL, max_position);
    if (error.occurred) {
      fail("unable to parse string: %s", error.message);
      return 0;
    }

    break;

  case IO_CHANNEL_FILE:
  case IO_CHANNEL_SOCK:
    buffer_release(&buffer);
    buffer = buffer_init(peek_size);
    buffer_alloc(&buffer, peek_size);
    string = buffer_data(&buffer, 0);

    io_peek(input, string, peek_size);
    if (error.occurred) {
      fail("unable to parse string: %s", error.message);
      return 0;
    }

    if (input->read_amount < peek_size)
      max_position = input->read_amount;

    break;
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
    buffer_release(&buffer);
    return position;
  }

  if (unlikely(character != '"' && position == 0)) {
    fail("not a string: missing initial '\"'");
    return 0;
  }

next_character:
  position++;
  if (position >= max_position) {
    fail("expected '\"' but found EOF");
    return 0;
  }

  switch (input->channel) {
  case IO_CHANNEL_MEM:
    goto read_character;

  case IO_CHANNEL_FILE:
  case IO_CHANNEL_SOCK:
    if (position < peek_size)
      goto read_character;

    peek_size *= 2;
    goto initialize;
  }

  return position;
}
