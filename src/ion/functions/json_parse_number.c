static inline struct sci_notation json_parse_number (
    struct io* input
)
{
  struct sci_notation number = { 0 };

  char* sign;
  char* digit;
  char* after_zero;

  char* parse_error;

check_sign:
  number.integer.content = (char*) input->data + input->cursor;

  sign = io_read(input, sizeof(char));
  if (error.occurred) {
    parse_error = "unable to read number sign";
    goto error;
  }

  if (sign == NULL) {
    parse_error = "expected a number but found EOF";
    goto error;
  }

  if (*sign == '-') {
    number.negative = true;
    number.integer.content++;
    goto integer_part;
  }

  if (*sign == '0')
    goto check_after_zero;

  if (isdigit(*sign)) {
    number.integer.length = 1;
    goto integer_part;
  }

  parse_error = "expected a number";
  goto error;

check_after_zero:
  after_zero = io_read(input, sizeof(char));
  if (error.occurred) {
    parse_error = "unable to check number after zero";
    goto error;
  }

  if (*after_zero == '.') {
    number.mantissa.content = (char*) input->data + input->cursor;
    goto mantissa_part;
  }

  if (*after_zero == 'E' || *after_zero == 'e') {
    number.exponent.content = (char*) input->data + input->cursor;
    goto check_exponent_sign;
  }

  if (*after_zero == 'x') {
    parse_error = "hexadecimal numbers are not valid JSON";
    goto error;
  }

  if (isdigit(*after_zero)) {
    parse_error = "octal numbers are not valid JSON";
    goto error;
  }

  return number;

integer_part:
  digit = io_read(input, sizeof(char));
  if (error.occurred) {
    parse_error = "unable to read the integer part";
    goto error;
  }

  if (digit == NULL) {
    if (number.integer.length == 0) {
      parse_error = "expected a number but found EOF";
      goto error;
    }

    return number;
  }

  if (isdigit(*digit)) {
    number.integer.length++;
    goto integer_part;
  }

  if (*digit == '.') {
    number.mantissa.content = (char*) input->data + input->cursor;
    goto mantissa_part;
  }

  if (*digit == 'E' || *digit == 'e') {
    number.exponent.content = (char*) input->data + input->cursor;
    goto check_exponent_sign;
  }

  return number;

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
  fail("%s", parse_error);
  return number;
}
