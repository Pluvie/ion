static inline struct sci_notation json_parse_number (
    struct io* input
)
{
  struct sci_notation number = { 0 };

  char* sign;
  char* digit;
  char* after_zero;
  char* after_integral;
  char* after_decimal;

  char* parse_error;

check_sign:
  sign = io_read(input, sizeof(char));
  if (error.occurred) {
    parse_error = "unable to read number sign";
    goto error;
  }

  if (*sign == '0') {
    number.integral.length = 1;
    goto check_after_zero;
  }

  if (isdigit(*sign)) {
    number.integral.length = 1;
    goto integral_part;
  }

  if (*sign == '-') {
    number.negative = true;
    goto integral_part;
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
    goto check_after_integral;

  case 'x':
    parse_error = "hexadecimal numbers are not valid JSON";
    goto error;

  default:
    if (isdigit(*after_zero)) {
      parse_error = "octal numbers are not valid JSON";
      goto error;
    }

    number.integral.content = (char*)
      (input->data + input->cursor - number.integral.length);
    return number;
  }

integral_part:
  digit = io_peek(input, sizeof(char));
  if (error.occurred) {
    if (io_exhausted(input))
      parse_error = "expected a number but found EOF";
    else
      parse_error = "unable to read the integral part";

    goto error;
  }

  if (isdigit(*digit)) {
    number.integral.length++;

    digit = io_read(input, sizeof(char));
    if (error.occurred) {
      parse_error = "unable to read the integral part";
      goto error;
    }

    goto integral_part;
  }

after_integral_part:
  switch(*digit) {
  case '.':
    after_integral = io_read(input, sizeof(char) * 2);

    if (error.occurred) {
      parse_error = "unable to read the fractional part";
      goto error;
    }

    if (isdigit(after_integral[1])) {
      number.fractional.length = 1;
      goto fractional_part;
    }

    parse_error = "expected number after decimal separator";
    goto error;

  case 'E':
  case 'e':
    after_integral = io_read(input, sizeof(char));

    if (error.occurred) {
      parse_error = "unable to read the exponent letter";
      goto error;
    }

    goto check_exponent_sign;

  default:
    number.integral.content = (char*)
      (input->data + input->cursor - number.integral.length);
    return number;
  }

fractional_part:
  digit = io_peek(input, sizeof(char));
  if (error.occurred) {
    if (io_exhausted(input))
      parse_error = "expected a number but found EOF";
    else
      parse_error = "unable to read the fractional part";

    goto error;
  }

  if (isdigit(*digit)) {
    number.fractional.length++;

    digit = io_read(input, sizeof(char));
    if (error.occurred) {
      parse_error = "unable to read the fractional part";
      goto error;
    }

    goto fractional_part;
  }

after_fractional_part:
  switch(*digit) {
  case 'E':
  case 'e':
    after_fractional = io_read(input, sizeof(char));

    if (error.occurred) {
      parse_error = "unable to read the exponent letter";
      goto error;
    }

    goto check_exponent_sign;

  default:
    number.fractional.content = (char*)
      (input->data + input->cursor - number.fractional.length);
    return number;
  }

check_exponent_sign:
  sign = io_read(input, sizeof(char));
  if (error.occurred) {
    parse_error = "unable to check the exponent sign";
    goto error;
  }

  if (*sign == '+')
    goto exponent_part;

  if (*sign == '-') {
    number.negative_exponent = true;
    goto exponent_part;
  }

  if (isdigit(*sign)) {
    number.exponent.length = 1;
    goto exponent_part;
  }

  parse_error = "expected an exponent";
  goto error;

exponent_part:
  digit = io_peek(input, sizeof(char));
  if (error.occurred) {
    if (io_exhausted(input))
      parse_error = "expected a number but found EOF";
    else
      parse_error = "unable to read the exponent part";

    goto error;
  }

  if (isdigit(*digit)) {
    number.exponent.length++;

    digit = io_read(input, sizeof(char));
    if (error.occurred) {
      parse_error = "unable to read the exponent part";
      goto error;
    }

    goto exponent_part;
  }

  number.exponent.content = (char*)
    (input->data + input->cursor - number.exponent.length);
  return number;

error:
  if (error.occurred)
    fail("%s: %s", parse_error, error.message);
  else
    fail("%s", parse_error);

  return number;
}
