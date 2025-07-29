static inline int json_parse_number (
    struct io* io
)
{
  int cursor = io_cursor_save(io);
  int length = 0;
  slice result;
  #define digit ((char*) result.data)[0]

  result = io_read(io, sizeof(char));
  if (error.occurred)
    goto error;

  if (result.length == 0)
    return 0;

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
  result = io_read(io, sizeof(char));
  if (error.occurred)
    goto error;

  if (result.length == 0)
    goto terminate;

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
  result = io_read(io, sizeof(char));
  if (error.occurred)
    goto error;

  if (result.length == 0)
    goto terminate;

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
  result = io_read(io, sizeof(char));
  if (error.occurred)
    goto error;

  if (result.length == 0)
    goto error;

  if (isdigit(digit)) {
    length++;
    goto fractional_part;
  }

  goto error;

fractional_part:
  result = io_read(io, sizeof(char));
  if (error.occurred)
    goto error;

  if (result.length == 0)
    goto terminate;

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
  result = io_read(io, sizeof(char));
  if (error.occurred)
    goto error;

  if (result.length == 0)
    goto error;

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
  result = io_read(io, sizeof(char));
  if (error.occurred)
    goto error;

  if (result.length == 0)
    goto terminate;

  if (isdigit(digit)) {
    length++;
    goto exponent_part;
  }

terminate:
  io_cursor_restore(io, cursor);
  return length;

error:
  io_cursor_restore(io, cursor);
  return -1;

  #undef digit
}
