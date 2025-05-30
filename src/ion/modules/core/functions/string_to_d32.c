d32 string_to_d32 (
    string source
)
{
  char* last_parsed_char = NULL;
  u64 parsed_chars_count = 0;

  errno = 0;
  d128 value = strtold(source.content, &last_parsed_char);

  parsed_chars_count = last_parsed_char - source.content;
  if (parsed_chars_count < source.length) {
    fail("cannot convert `%.*s` to d32: invalid characters detected", sp(source));
    return 0;
  }

  if (errno == ERANGE) {
    fail("cannot convert `%.*s` to d32: value overflow", sp(source));
    return 0;
  }

  if (value > D32_MAX || value < D32_MIN) {
    fail("cannot convert `%.*s` to i32: value overflow", sp(source));
    return 0;
  }

  return (d32) value;
}
