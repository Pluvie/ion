
  /* Procedure prerequisites on local variables:
   *
   * - `cursor` must be a `char*`: it must point to the number to be parsed, with at
   *   least one padding character at the end. This means that the last character of
   *   the string must not be the last valid character of the number to parse.
   * - `result` must be a `int` or `dec`, depending on which type the parser
   *   must output. */

  char* begin = cursor;

#ifndef STRING_TO_NUMBER__DISCARD
  int number = 0;
  int exponent = 0;
  int accumulator = 0;
  bool negative = false;
  bool negative_exponent = false;

  int integral_length = 0;
  int decimal_length = 0;
  int exponent_length = 0;

  char* integral_start = cursor;
  char* decimal_start = cursor;
  char* exponent_start = cursor;
#endif

  /* Number starts with 1-9. Go parse the integral part. */
  if (*cursor >= '1' && *cursor <= '9')
    goto parse_integral;

  /* Number starts with 0. Cannot contain any digit afterwards. */
  if (*cursor == '0') {
    cursor++;

    /* Non-numbers or numbers starting with 0 and with any other digit afterwards. */
    if (*cursor == '.')
      goto parse_decimal;
    else if (*cursor >= '0' && *cursor <= '9')
      goto parse_failure;
    else
      goto parse_success;
  }

  /* Number does not start with 0-9 and neither with '-': it's not valid. */
  if (*cursor != '-')
    goto parse_failure;

  /* Number starts with '-'. Advances the pointer and, if not discarding, remembers
   * that it was negative in order to change its sign at the end. Then proceeds to
   * parse the integral part. */
  cursor++;
#ifndef STRING_TO_NUMBER__DISCARD
  negative = true;
  integral_start++;
#endif
  goto parse_integral;


parse_integral:
  #include "string_to_number_parse_digit.c"

#ifndef STRING_TO_NUMBER__DISCARD
  integral_length = cursor - integral_start;
#endif

  if (*cursor == '.')
    goto parse_decimal;
  else if (*cursor == 'e' || *cursor == 'E')
    goto parse_exponent;

#ifndef STRING_TO_NUMBER__DISCARD
  number = accumulator;
#endif
  goto parse_success;


parse_decimal:
  cursor++;
#ifndef STRING_TO_NUMBER__DISCARD
  decimal_start = cursor;
#endif

  if (*cursor >= '0' && *cursor <= '9')
    #include "string_to_number_parse_digit.c"
  else
    goto parse_failure;

#ifndef STRING_TO_NUMBER__DISCARD
  number = accumulator;
  decimal_length = cursor - decimal_start;
#endif

  if (*cursor != 'e' && *cursor != 'E')
    goto parse_success;


parse_exponent:
  cursor++;

  if (*cursor == '-') {
    cursor++;
#ifndef STRING_TO_NUMBER__DISCARD
    negative_exponent = true;
#endif
  } else if (*cursor == '+') {
    cursor++;
  }

#ifndef STRING_TO_NUMBER__DISCARD
  number = accumulator;
  accumulator = 0;
  exponent_start = cursor;
#endif

  if (*cursor >= '0' && *cursor <= '9') {
    #include "string_to_number_parse_digit.c"
#ifndef STRING_TO_NUMBER__DISCARD
    exponent = accumulator;
    exponent_length = cursor - exponent_start;
#endif
    goto parse_success;

  } else {
    goto parse_failure;
  }


parse_failure:
#ifndef STRING_TO_NUMBER__DISCARD
  if (cursor == begin) {
    fail("expected a number");
  } else {
    fail("invalid number");
  }
#else
  cursor = begin;
#endif
  goto procedure_failure;


parse_success:
#ifdef STRING_TO_NUMBER__DISCARD
  goto procedure_success;

#else
  dec number_dec = 0;

  if (number == 0)
    goto convert_result;

  if (negative_exponent)
    exponent = -exponent;

  int exponent_offset = exponent - decimal_length;
  int number_length = integral_length + decimal_length;

  /* Overflow checks. */
  if (unlikely(number_length > INT_MAXCHARS || clz(number) == 0)) {
    fail("number overflow");
    goto procedure_failure;
  }

  if (unlikely(exponent_length > DEC_EXP_MAXCHARS || exponent > DEC_EXP_MAX)) {
    fail("exponent overflow");
    goto procedure_failure;
  }

#ifdef STRING_TO_NUMBER__INTEGER
  if (unlikely(integral_length + exponent_offset >= INT_MAXCHARS)) {
    fail("exponent overflow");
    goto procedure_failure;
  }
#endif
  /* End of overflow checks. */

  if (exponent_offset == 0)
    number_dec = (dec) number;
  else if (exponent_offset < 0)
    number_dec = (dec) number / powers_of_ten[-exponent_offset];
  else
    number_dec = (dec) number * powers_of_ten[exponent_offset];

convert_result:
#ifdef STRING_TO_NUMBER__INTEGER
  result = (int) number_dec;
#endif
  
#ifdef STRING_TO_NUMBER__DECIMAL
  result = number_dec;
#endif

  if (negative)
    result = -result;

  goto procedure_success;
#endif
