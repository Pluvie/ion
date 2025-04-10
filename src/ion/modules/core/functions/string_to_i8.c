i8 string_to_i8 (
    string source
)
{
  char* last_parsed_char = NULL;
  u64 parsed_chars_count = 0;

  errno = 0;
  i64 value = strtoll(source.content, &last_parsed_char, 0);

  parsed_chars_count = last_parsed_char - source.content;
  if (parsed_chars_count < source.length) {
    fail("cannot convert `%.*s` to i8: invalid characters detected", sp(source));
    return 0;
  }

  if (errno == ERANGE) {
    fail("cannot convert `%.*s` to i8: value overflow", sp(source));
    return 0;
  }

  if (value > I8_MAX || value < I8_MIN) {
    fail("cannot convert `%.*s` to i8: value overflow", sp(source));
    return 0;
  }

  return (i8) value;
}
