int string_to_int (
    string source
)
{
  char* last_parsed_char = NULL;
  int parsed_chars_count = 0;

  errno = 0;
  int value = strtoll(source.content, &last_parsed_char, 0);

  parsed_chars_count = last_parsed_char - source.content;
  if (parsed_chars_count < source.length) {
    fail("cannot convert `%.*s` to int: invalid characters detected", sp(source));
    return 0;
  }

  if (errno == ERANGE) {
    fail("cannot convert `%.*s` to int: value overflow", sp(source));
    return 0;
  }

  return (int) value;
}
