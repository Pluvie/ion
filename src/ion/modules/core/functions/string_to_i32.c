i32 string_to_i32 (
    string source
)
{
  char* last_parsed_char = NULL;
  u64 parsed_chars_count = 0;

  errno = 0;
  i64 value = strtoll(source.content, &last_parsed_char, 0);

  parsed_chars_count = last_parsed_char - source.content;
  if (parsed_chars_count < source.length) {
    fail("cannot convert `%.*s` to i32: invalid characters detected", sp(source));
    return 0;
  }

  if (errno == ERANGE) {
    fail("cannot convert `%.*s` to i32: value overflow", sp(source));
    return 0;
  }

  if (value > I32_MAX || value < I32_MIN) {
    fail("cannot convert `%.*s` to i32: value overflow", sp(source));
    return 0;
  }

  return (i32) value;
}
