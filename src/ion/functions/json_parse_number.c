int json_parse_number (
    struct io* io
)
{
  int cursor = io_cursor_save(io);
  int length = 0;
  char digit;

  io_read(io, sizeof(char));
  if (unlikely(failure.occurred))
    goto error;

  digit = string_char_at(io->result, 0);
  if (digit == '-') {
    length++;
    goto integral_part;
  }

  if (digit == '0') {
    length++;
    goto check_after_zero;
  }

  if (isdigit(digit)) {
    length++;
    goto integral_part;
  }

  goto error;

check_after_zero:
  io_read(io, sizeof(char));
  if (unlikely(failure.occurred))
    goto error;

  if (io->result.length == 0)
    goto terminate;

  digit = string_char_at(io->result, 0);
  switch(digit) {
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
  io_read(io, sizeof(char));
  if (unlikely(failure.occurred))
    goto error;

  if (io->result.length == 0)
    goto terminate;

  digit = string_char_at(io->result, 0);
  if (isdigit(digit)) {
    length++;
    goto integral_part;
  }

  if (digit == '.') {
    length++;
    goto check_after_decimal_separator;
  }

  if (digit == 'e' || digit == 'E') {
    length++;
    goto exponent_sign;
  }

  goto terminate;

check_after_decimal_separator:
  io_read(io, sizeof(char));
  if (unlikely(failure.occurred))
    goto error;

  if (io->result.length == 0)
    goto error;

  digit = string_char_at(io->result, 0);
  if (isdigit(digit)) {
    length++;
    goto fractional_part;
  }

  goto error;

fractional_part:
  io_read(io, sizeof(char));
  if (unlikely(failure.occurred))
    goto error;

  if (io->result.length == 0)
    goto terminate;

  digit = string_char_at(io->result, 0);
  if (isdigit(digit)) {
    length++;
    goto fractional_part;
  }

  if (digit == 'e' || digit == 'E') {
    length++;
    goto exponent_sign;
  }

  goto terminate;

exponent_sign:
  io_read(io, sizeof(char));
  if (unlikely(failure.occurred))
    goto error;

  if (io->result.length == 0)
    goto error;

  digit = string_char_at(io->result, 0);
  switch (digit) {
  case '-':
  case '+':
    length++;
    goto exponent_part;
  default:
    if (isdigit(digit)) {
      length++;
      goto exponent_part;
    }

    goto error;
  }

exponent_part:
  io_read(io, sizeof(char));
  if (unlikely(failure.occurred))
    goto error;

  if (io->result.length == 0)
    goto terminate;

  digit = string_char_at(io->result, 0);
  if (isdigit(digit)) {
    length++;
    goto exponent_part;
  }

terminate:
  io_cursor_restore(io, cursor);
  io_read(io, length);
  return length;

error:
  io_cursor_restore(io, cursor);
  return -1;
}
