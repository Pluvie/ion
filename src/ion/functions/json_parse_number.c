static inline bool json_parse_number (
    struct io* source,
    struct sci_notation* number
)
{
  u64 initial_cursor_position = source->cursor;
  u64 position = 0;

  char sign;
  char digit;
  char after_zero;

initialize:
  char* buffer = io_read(source, 1024);
  if (error.occurred)
    return false;

  source->cursor = initial_cursor_position;
  memzero(number, sizeof(struct sci_notation));

check_sign:
  sign = buffer[0];
  position++;

  if (sign == '-') {
    number->negative = true;
    number->integral.content = buffer + position;
    goto integral_part;
  }

  if (sign == '0') {
    number->integral.content = buffer + 0;
    number->integral.length = 1;
    goto check_after_zero;
  }

  if (isdigit(sign)) {
    number->integral.content = buffer + 0;
    number->integral.length = 1;
    goto integral_part;
  }

  return false;

check_after_zero:
  after_zero = buffer[1];
  position++;

  switch(after_zero) {
  case '.':
    number->fractional.content = buffer + position;
    goto fractional_part;
  case 'E':
  case 'e':
    number->exponent.content = buffer + position;
    goto exponent_part;

  case 'x':
    /* Hexadecimal numbers are not valid JSON. */
    return false;

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
    return false;

  default:
    return true;
  }

integral_part:
  if (position >= source->read_amount)
    return true;

  digit = buffer[position];
  position++;

  if (isdigit(digit)) {
    number->integral.length++;
    goto integral_part;
  }

  if (digit == '.') {
    number->fractional.content = buffer + position;

    if (!isdigit(buffer[position])) {
      fail("expected a digit after the decimal separator");
      return false;
    }

    goto fractional_part;
  }

  if (digit == 'e' || digit == 'E') {
    number->exponent.content = buffer + position;
    goto exponent_sign;
  }

  return true;

fractional_part:
  if (position >= source->read_amount)
    return true;

  digit = buffer[position];
  position++;

  if (isdigit(digit)) {
    number->fractional.length++;
    goto fractional_part;
  }

  if (digit == 'e' || digit == 'E') {
    number->exponent.content = buffer + position;
    goto exponent_sign;
  }

  return true;

exponent_sign:
  sign = buffer[position];
  position++;

  switch (sign) {
  case '-':
    number->negative_exponent = true;
    number->exponent.content = buffer + position;
    goto exponent_part;
  case '+':
    number->exponent.content = buffer + position;
    goto exponent_part;
  default:
    if (isdigit(sign)) {
      number->exponent.length = 1;
      number->exponent.content = buffer + position - 1;
      goto exponent_part;
    }

    fail("expected sign or digit after exponent");
    return false;
  }

exponent_part:
  if (position >= source->read_amount)
    return true;

  digit = buffer[position];
  position++;

  if (isdigit(digit)) {
    number->exponent.length++;
    goto exponent_part;
  }

  return true;
}
