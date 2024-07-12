static inline void json_decode_spaces (
    struct io* input,
    struct io* output,
    struct protocol* json
)
{
  if (input->cursor >= input->length)
    return;

  char* current;

  do {
    current = (char*) input->data + input->cursor;

    if (!isspace(*current))
      break;

    current = io_read(input, sizeof(char));
  } while (current != NULL);
}
