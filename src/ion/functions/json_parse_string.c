static inline u64 json_parse_string (
    struct io* input
)
{
  char* string = NULL;
  char* parse_error = NULL;
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
    if (error.occurred)
      goto error;

    break;

  case IO_CHANNEL_FILE:
  case IO_CHANNEL_SOCK:
    buffer_release(&buffer);
    buffer = buffer_init(peek_size);
    buffer_alloc(&buffer, peek_size);
    string = buffer_data(&buffer, 0);

    io_peek(input, string, peek_size);
    if (error.occurred)
      goto error;

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
    parse_error = "not a string: missing initial '\"'";
    goto error;
  }

next_character:
  position++;
  if (position >= max_position) {
    parse_error = "expected '\"' but found EOF";
    goto error;
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

error:
  if (error.occurred) {
    fail("%s: %s", parse_error, error.message);
  } else {
    fail("%s", parse_error);
  }

  return 0;
}
