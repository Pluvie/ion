u64 string_to_u64 (
    string source
)
{
  char* last_parsed_char = NULL;
  u64 parsed_chars_count = 0;

  errno = 0;
  u64 value = strtoull(source.content, &last_parsed_char, 0);

  parsed_chars_count = last_parsed_char - source.content;
  if (parsed_chars_count < source.length) {
    fail("cannot convert `%.*s` to u64: invalid characters detected", sp(source));
    return 0;
  }

  if (errno == ERANGE) {
    fail("cannot convert `%.*s` to u64: value overflow", sp(source));
    return 0;
  }

  return value;
}
