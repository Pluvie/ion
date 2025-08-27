dec string_to_dec (
    string source
)
{
  char* last_parsed_char = NULL;
  int parsed_chars_count = 0;

  errno = 0;
  dec value = strtold(source.pointer, &last_parsed_char);

  parsed_chars_count = last_parsed_char - (char*) source.pointer;
  if (parsed_chars_count < source.length) {
    fail("cannot convert `%.*s` to dec: invalid characters detected", sp(source));
    return 0;
  }

  if (errno == ERANGE) {
    fail("cannot convert `%.*s` to dec: value overflow", sp(source));
    return 0;
  }

  return (dec) value;
}
