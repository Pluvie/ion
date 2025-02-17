static inline struct string json_parse_string (
    struct io* input
)
{
  char* current;
  struct string result = { 0 };

  if (io_exhausted(input)) {
    fail("expected '\"' but found EOF");
    goto parse_error;
  }

initial_double_quote:
  current = io_peek(input, sizeof(char));

  if (*current != '"') {
    fail("not a string: missing initial '\"'");
    goto parse_error;
  }

  result.content = current;

string_content:
  result.length++;
  current = io_read(input, sizeof(char));

  if (io_exhausted(input)) {
    fail("unterminated string: missing final '\"'");
    goto parse_error;
  }

  current = io_peek(input, sizeof(char));

  if (*current == 92)
    goto escape;

  if (*current != '"')
    goto string_content;

final_double_quote:
  io_read(input, sizeof(char));
  result.length++;
  return result;

escape:
  io_read(input, sizeof(char));
  current = io_peek(input, sizeof(char));

  if (*current != '"')
    goto string_content;

  io_read(input, sizeof(char));
  result.length++;
  goto string_content;


parse_error:
  result.content = NULL;
  result.length = 0;
  return result;
}
