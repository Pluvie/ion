static inline void json_parse_number (
    struct io* input,
    enum types type,
    void* result
)
{
  struct sci_notation number = { 0 };

  char buffer[256] = { 0 };
  u64 position = 0;

  char sign;
  char digit;
  char after_zero;

  struct { char content[128]; u64 begin; u64 length; } integral = { 0 };
  struct { char content[128]; u64 begin; u64 length; } fractional = { 0 };
  struct { char content[32];  u64 begin; u64 length; } exponent = { 0 };

initialize:
  io_peek(input, buffer, sizeof(buffer));
  if (error.occurred) {
    fail("error while parsing number: %s", error.message);
    return;
  }

check_sign:
  sign = buffer[0];
  position++;

  if (sign == '-') {
    number.negative = true;
    integral.begin = 1;
    goto integral_part;
  }

  if (sign == '0') {
    integral.begin = 0;
    integral.length = 1;
    goto check_after_zero;
  }

  if (isdigit(sign)) {
    integral.begin = 0;
    integral.length = 1;
    goto integral_part;
  }

  fail("expected a number");
  return;

check_after_zero:
  after_zero = buffer[1];
  position++;

  switch(after_zero) {
  case '.':
  case 'E':
  case 'e':
    if (after_zero == '.')
      goto fractional_part;
    else
      goto exponent_part;

  case 'x':
    fail("hexadecimal numbers are not valid JSON");
    return;

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
    fail("octal numbers are not valid JSON");
    return;

  default:
    goto terminate;
  }

integral_part:
  if (position >= sizeof(buffer)) {
    fail("number too big");
    return;
  }

  digit = buffer[position];
  position++;

  if (isdigit(digit)) {
    integral.length++;
    goto integral_part;
  }

  if (digit == '.') {
    fractional.begin = position;

    if (!isdigit(buffer[position])) {
      fail("expected a digit after the decimal separator");
      return;
    }

    goto fractional_part;
  }

  if (digit == 'e' || digit == 'E') {
    exponent.begin = position;
    goto exponent_sign;
  }

  goto terminate;

fractional_part:
  if (position >= sizeof(buffer)) {
    fail("number too big");
    return;
  }

  digit = buffer[position];
  position++;

  if (isdigit(digit)) {
    fractional.length++;
    goto fractional_part;
  }

  if (digit == 'e' || digit == 'E') {
    exponent.begin = position;
    goto exponent_sign;
  }

  goto terminate;

exponent_sign:
  sign = buffer[position];
  position++;

  switch (sign) {
  case '-':
    number.negative_exponent = true;
    exponent.begin = position;
    goto exponent_part;
  case '+':
    exponent.begin = position;
    goto exponent_part;
  default:
    if (isdigit(sign)) {
      exponent.length = 1;
      exponent.begin = position - 1;
      goto exponent_part;
    }

    fail("expected sign or digit after exponent");
    return;
  }

exponent_part:
  if (position >= sizeof(buffer)) {
    fail("number too big");
    return;
  }

  digit = buffer[position];
  position++;

  if (isdigit(digit)) {
    exponent.length++;
    goto exponent_part;
  }

  goto terminate;

terminate:
  memcpy(integral.content, buffer + integral.begin, integral.length);
  if (fractional.length > 0)
    memcpy(fractional.content, buffer + fractional.begin, fractional.length);
  if (exponent.length > 0)
    memcpy(exponent.content, buffer + exponent.begin, exponent.length);

  number.integral.length = integral.length;
  number.integral.content = integral.content;
  number.fractional.length = fractional.length;
  number.fractional.content = fractional.content;
  number.exponent.length = exponent.length;
  number.exponent.content = exponent.content;

  sci_notation_convert(&number, type, result);
  if (error.occurred) {
    fail("unable to convert number: %s", error.message);
    return;
  }
}
