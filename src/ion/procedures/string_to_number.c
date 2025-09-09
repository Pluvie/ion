
  /* Variable prerequisites:
   * - `source` must be a `string*`: it must contain the number to be parsed, with at
   *   least one '\0' padding character at the end.
   * - `result` must be a `int` or `dec`, depending on which type the parser
   *   must output.
   *
   * The `end` variable can be used in case of a parsing failure in order to give more
   * information on the failure reason. If it is equal to `source->pointer`, no valid
   * characters were found. Otherwise, some valid characters were found up until a
   * mandatory expected character, which was not found. These are mostly incomplete
   * numbers situations like `3.` or `3.14e`. */
  char* cursor = source->pointer;

#ifndef STRING_TO_NUMBER__DISCARD
  int number = 0;
  int exponent = 0;
  int accumulator = 0;
  bool negative = false;
  bool negative_exponent = false;

  int integral_length = 0;
  int decimal_length = 0;
  //int exponent_length = 0;

  char* integral_start = source->pointer;
  char* decimal_start = source->pointer;
  //char* exponent_start = source->pointer;
#endif

  /* Number starts with 0-9. Go parse the integral part. */
  if (*cursor >= '0' && *cursor <= '9')
    goto parse_integral;

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

  /* Non-numbers or numbers starting with 0 and with any other digit afterwards. */
  if (integral_length == 0 || (*integral_start == '0' && integral_length > 1))
    goto parse_failure;

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
  decimal_start = cursor;

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
    negative_exponent = true;
  } else if (*cursor == '+') {
    cursor++;
  }

#ifndef STRING_TO_NUMBER__DISCARD
  number = accumulator;
  accumulator = 0;
  //exponent_start = cursor;
#endif

  if (*cursor >= '0' && *cursor <= '9') {
    #include "string_to_number_parse_digit.c"
#ifndef STRING_TO_NUMBER__DISCARD
    exponent = accumulator;
    //exponent_length = cursor - exponent_start;
#endif
    goto parse_success;

  } else {
    goto parse_failure;
  }

parse_failure:
  if (cursor == source->pointer) {
    fail("expected a number");
  } else {
    fail("invalid number");
  }

  source->pointer = cursor;
  goto procedure_failure;

parse_success:
  source->pointer = cursor;
#ifdef STRING_TO_NUMBER__DISCARD
  goto procedure_success;

#else
  /* Overflow checks. */
  //if (exponent_length > 3 && exponent > DEC_EXP_MAX)

  /* End of overflow checks. */

  if (negative_exponent)
    exponent = -exponent;

  if (exponent != 0)
    decimal_length -= exponent;

  dec number_dec = 0;

  if (decimal_length > 0)
    number_dec = (dec) number / (dec) powers_of_ten[decimal_length];
  else if (decimal_length < 0)
    number_dec = (dec) number * (dec) powers_of_ten[-decimal_length];
  else
    number_dec = (dec) number;
  
  print("");
  print("----> exponent: |%li|", exponent);
  print("----> decimal length: |%li|", decimal_length);
  print("---------> parsed: |%f|", number_dec);
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
