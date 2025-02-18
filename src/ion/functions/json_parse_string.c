static inline struct string json_parse_string (
    struct io* input
)
{
  struct string result = { 0 };
  char* parse_error;
  char* character;

initial_double_quote:
  character = io_read(input, sizeof(char));
  if (error.occurred) {
    parse_error = "unable to read first double quote";
    goto error;
  }

  if (*character != '"') {
    parse_error = "not a string: missing initial '\"'";
    goto error;
  }

string_content:
  character = io_read(input, sizeof(char));
  if (error.occurred) {
    if (io_exhausted(input))
      parse_error = "unterminated string: missing final '\"'";
    else
      parse_error = "unable to read content";

    goto error;
  }

  result.length++;

  if (*character == 92)
    goto escape_character;

  if (*character != '"')
    goto string_content;

  goto finalize_result;

escape_character:
  character = io_read(input, sizeof(char));
  if (error.occurred) {
    if (io_exhausted(input))
      parse_error = "unterminated string: missing final '\"'";
    else
      parse_error = "unable to read escaped character";

    goto error;
  }

  result.length++;

  goto string_content;

finalize_result:
  switch(input->channel) {
  case IO_CHANNEL_MEM:
  case IO_CHANNEL_FILE:
    result.content = (char*)
      (input->data + input->cursor - result.length);
    break;
  case IO_CHANNEL_SOCK:
    result.content = (char*)
      buffer_data(input->allocator, input->allocator->position - result.length);
    break;
  }

  result.length--;
  return result;

error:
  fail("%s", parse_error);
  result.content = NULL;
  result.length = 0;
  return result;
}
