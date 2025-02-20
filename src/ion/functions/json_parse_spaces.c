static inline u64 json_parse_spaces (
    struct io* input
)
{
  char* spaces = NULL;

  u64 position = 0;
  u64 max_position = U64_MAX;

  char character;

  u64 peek_size = 256;
  struct buffer buffer = { 0 };

initialize:
  switch (input->channel) {
  case IO_CHANNEL_MEM:
    max_position = input->length - input->cursor;

    spaces = io_peek(input, NULL, max_position);
    if (error.occurred) {
      fail("unable to parse spaces: %s", error.message);
      return 0;
    }

    break;

  case IO_CHANNEL_FILE:
  case IO_CHANNEL_SOCK:
    buffer_release(&buffer);
    buffer = buffer_init(peek_size);
    buffer_alloc(&buffer, peek_size);
    spaces = buffer_data(&buffer, 0);

    io_peek(input, spaces, peek_size);
    if (error.occurred) {
      fail("unable to parse spaces: %s", error.message);
      return 0;
    }

    if (input->read_amount < peek_size)
      max_position = input->read_amount;

    break;
  }

read_character:
  character = spaces[position];

  if (!isspace(character)) {
    buffer_release(&buffer);
    return position;
  }

next_character:
  position++;
  if (position >= max_position) {
    fail("expected a space but found EOF");
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
