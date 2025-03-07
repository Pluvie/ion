static inline u64 json_parse_number (
    struct io* source
)
{
  io_cursor_save(source);

  char* digit;
  u64 length = 0;

check_sign:
  digit = io_read(source, sizeof(char));
  if (error.occurred)
    return 0;

  if (*digit == '-') {
    length++;
    goto integral_part;
  }

  if (*digit == '0') {
    length++;
    goto check_after_zero;
  }

  if (isdigit(*digit)) {
    length++;
    goto integral_part;
  }

  goto error;

check_after_zero:
  digit = io_read(source, sizeof(char));
  if (error.occurred)
    return 0;

  switch(*digit) {
  case '.':
    length++;
    goto fractional_part;
  case 'E':
  case 'e':
    length++;
    goto exponent_part;

  case 'x':
    /* Hexadecimal numbers are not valid JSON. */
    goto error;

  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
    /* Octal numbers are not valid JSON. */
    goto error;

  default:
    goto terminate;
  }

integral_part:
  if (io_exhausted(source))
    goto terminate;

  digit = io_read(source, sizeof(char));
  if (error.occurred)
    return 0;

  if (isdigit(*digit)) {
    length++;
    goto integral_part;
  }

  if (*digit == '.') {
    length++;
    goto check_after_decimal_separator;
  }

  if (*digit == 'e' || *digit == 'E') {
    length++;
    goto exponent_sign;
  }

  goto terminate;

check_after_decimal_separator:
  digit = io_read(source, sizeof(char));
  if (error.occurred)
    return 0;

  if (isdigit(*digit)) {
    length++;
    goto fractional_part;
  }

  fail("expected a digit after the decimal separator");
  goto error;

fractional_part:
  if (io_exhausted(source))
    goto terminate;

  digit = io_read(source, sizeof(char));
  if (error.occurred)
    return 0;

  if (isdigit(*digit)) {
    length++;
    goto fractional_part;
  }

  if (*digit == 'e' || *digit == 'E') {
    length++;
    goto exponent_sign;
  }

  goto terminate;

exponent_sign:
  digit = io_read(source, sizeof(char));
  if (error.occurred)
    return 0;

  switch (*digit) {
  case '-':
  case '+':
    length++;
    goto exponent_part;
  default:
    if (isdigit(*digit)) {
      length++;
      goto exponent_part;
    }

    fail("expected sign or digit after exponent");
    goto error;
  }

exponent_part:
  if (io_exhausted(source))
    goto terminate;

  digit = io_read(source, sizeof(char));
  if (error.occurred)
    return 0;

  if (isdigit(*digit)) {
    length++;
    goto exponent_part;
  }

terminate:
  io_cursor_restore(source);
  return length;

error:
  io_cursor_restore(source);
  return 0;
}
