static inline struct sci_notation json_parse_number (
    struct io* input
)
{
  struct sci_notation number = { 0 };

  char* sign;
  char* digit;
  char* after_zero;
  char* after_integer;

  char* parse_error;

check_sign:
  sign = io_read(input, sizeof(char));
  if (error.occurred) {
    parse_error = "unable to read number sign";
    goto error;
  }

  if (*sign == '0') {
    number.integer.length = 1;
    goto check_after_zero;
  }

  if (isdigit(*sign)) {
    number.integer.length = 1;
    goto integer_part;
  }

  if (*sign == '-') {
    number.negative = true;
    goto integer_part;
  }

  parse_error = "expected a number";
  goto error;

check_after_zero:
  after_zero = io_peek(input, sizeof(char));
  if (error.occurred) {
    parse_error = "unable to check number after zero";
    goto error;
  }

  switch(*after_zero) {
  case '.':
  case 'E':
  case 'e':
    goto check_after_integer;

  case 'x':
    parse_error = "hexadecimal numbers are not valid JSON";
    goto error;

  default:
    if (isdigit(*after_zero)) {
      parse_error = "octal numbers are not valid JSON";
      goto error;
    }

    number.integer.content = (char*)
      (input->data + input->cursor - number.integer.length);
    return number;
  }

integer_part:
  digit = io_peek(input, sizeof(char));
  if (error.occurred) {
    if (io_exhausted(input))
      parse_error = "expected a number but found EOF";
    else
      parse_error = "unable to read the integer part";

    goto error;
  }

  if (isdigit(*digit)) {
    number.integer.length++;

    digit = io_read(input, sizeof(char));
    if (error.occurred) {
      parse_error = "unable to read the integer part";
      goto error;
    }

    goto integer_part;
  }

  switch(*digit) {
  case '.':
  case 'E':
  case 'e':
    goto check_after_integer;

  default:
    number.integer.content = (char*)
      (input->data + input->cursor - number.integer.length);
    return number;
  }

check_after_integer:
  after_integer = io_read(input, sizeof(char) * 2);

  if (error.occurred) {
    parse_error = "unable to check after integer";
    goto error;
  }

  if (!isdigit(after_integer[1])) {
    if (after_integer[0] == '.')
    parse_error = "expected number after decimal";
    goto error;
  }

  if (after_integer[0] == '.')
    goto mantissa_part;
  else
    goto check_exponent_sign;

mantissa_part:
  digit = io_read(input, sizeof(char));
  if (error.occurred) {
    parse_error = "unable to read the mantissa part";
    goto error;
  }

  if (digit == NULL) {
    if (number.mantissa.length == 0) {
      parse_error = "expected a mantissa but found EOF";
      goto error;
    }

    return number;
  }

  if (isdigit(*digit)) {
    number.mantissa.length++;
    goto mantissa_part;
  }

  if (*digit == 'E' || *digit == 'e') {
    number.exponent.content = (char*) input->data + input->cursor;
    goto check_exponent_sign;
  }

  if (number.mantissa.length == 0) {
    parse_error = "expected a mantissa";
    goto error;
  }

  return number;

check_exponent_sign:
  sign = io_read(input, sizeof(char));
  if (error.occurred) {
    parse_error = "unable to check the exponent sign";
    goto error;
  }

  if (sign == NULL) {
    parse_error = "expected an exponent but found EOF";
    goto error;
  }

  if (*sign == '+') {
    number.exponent.content++;
    goto exponent_part;
  }

  if (*sign == '-') {
    number.negative_exponent = true;
    number.exponent.content++;
    goto exponent_part;
  }

  if (isdigit(*sign)) {
    number.exponent.length++;
    goto exponent_part;
  }

  parse_error = "expected an exponent";
  goto error;

exponent_part:
  digit = io_read(input, sizeof(char));
  if (error.occurred) {
    parse_error = "unable to read the exponent part";
    goto error;
  }

  if (digit == NULL)
    return number;

  if (isdigit(*digit)) {
    number.exponent.length++;
    goto exponent_part;
  }

  return number;

error:
  if (error.occurred)
    fail("%s: %s", parse_error, error.message);
  else
    fail("%s", parse_error);

  return number;
}
