/*
  This procedure contains the number parsing logic for both integers and decimals,
  written in base 10.

  These are the procedure prerequisites on local variables:

  - `cursor` must be a `char*`: it must point to the number to be parsed, with at
    least one padding character at the end. This means that the last character of
    the string must not be the last valid character of the number to parse.
  - `result` must be a `int` or `dec`, depending on which type the parser
    must output.

  The procedure recognizes numbers in the following format, which is locale independent:

    - The number may start with a minus `-` sign.
    - The number must start with just a `0` or `[1-9]+`: this means that more than
      one leading zeros are not allowed (i.e. `0003` is not valid, to avoid conflicts
      with octal representation).
    - The number may be followed by a decimal separator `.`. If this is the case, the
      separator must be followed by at least one digit `[0-9]+`.
    - The number may be followed by an exponent `e` or `E`. If this is the case, the
      exponent letter must be followed by at least one digit `[0-9]+` optionally
      preceded by a sign `-` or `+`.

  The procedure shall look for these constants, and trigger some specific behaviour
  if they are defined:

    - `PARSE_NUMBER__DISCARD`: if this constant is defined, then the parsing shall
      complete its execution but no result shall be given. This optimizes performance
      when the input must be consumed but the parsing result is not necessary.
    - `PARSE_NUMBER__INTEGER`: if this constant is defined, the parsing shall
      return an integer on the `result` local variable -- which must be an `int`.
      If the number had any fractional part, it shall be discarded. If the number
      had an exponent, it shall be calculated and any resulting fractional part shall
      be discarded.
    - `PARSE_NUMBER__DECIMAL`: if this constant is defined, the parsing shall
      return a decimal on the `result` local variable -- which must be a `dec`.
*/

  char* begin = cursor;

#ifndef PARSE_NUMBER__DISCARD
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

  /* Number starts with '-'. Advances the cursor and, if not discarding, remembers
    that it was negative in order to change its sign at the end. Then proceeds to
    parse the integral part.  */
  cursor++;
#ifndef PARSE_NUMBER__DISCARD
  negative = true;
  integral_start++;
#endif
  goto parse_integral;


parse_integral:
  #include "parse_digit.c"

#ifndef PARSE_NUMBER__DISCARD
  integral_length = cursor - integral_start;
#endif

  if (*cursor == '.')
    goto parse_decimal;
  else if (*cursor == 'e' || *cursor == 'E')
    goto parse_exponent;

#ifndef PARSE_NUMBER__DISCARD
  number = accumulator;
#endif
  goto parse_success;


parse_decimal:
  cursor++;
#ifndef PARSE_NUMBER__DISCARD
  decimal_start = cursor;
#endif

  if (*cursor >= '0' && *cursor <= '9')
    #include "parse_digit.c"
  else
    goto parse_failure;

#ifndef PARSE_NUMBER__DISCARD
  number = accumulator;
  decimal_length = cursor - decimal_start;
#endif

  if (*cursor != 'e' && *cursor != 'E')
    goto parse_success;


parse_exponent:
  cursor++;

  if (*cursor == '-') {
    cursor++;
#ifndef PARSE_NUMBER__DISCARD
    negative_exponent = true;
#endif
  } else if (*cursor == '+') {
    cursor++;
  }

#ifndef PARSE_NUMBER__DISCARD
  number = accumulator;
  accumulator = 0;
  exponent_start = cursor;
#endif

  if (*cursor >= '0' && *cursor <= '9') {
    #include "parse_digit.c"
#ifndef PARSE_NUMBER__DISCARD
    exponent = accumulator;
    exponent_length = cursor - exponent_start;
#endif
    goto parse_success;

  } else {
    goto parse_failure;
  }


parse_failure:
#ifndef PARSE_NUMBER__DISCARD
  if (cursor == begin)
    fail("expected a number");
  else
    fail("invalid number");
#else
  cursor = begin;
#endif
  goto procedure_failure;


parse_success:
#ifdef PARSE_NUMBER__DISCARD
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
  if (unlikely(number_length >= INT_MAXCHARS)) {
    if (number_length > INT_MAXCHARS) {
      /* If the number length is greater than the maximum chars that can be contained in
        an integer, then we have an overflow for sure. For example, on 32-bit systems,
        the maximum number of chars in an integer is 10: the highest integer is infact
        2147483647 (2^32 - 1), which is 10 characters long. So if we end up having 11 or
        more chars we have overflowed. */
      fail("number overflow");
      goto procedure_failure;
    }

    /* If the number length is equal than the maximum chars of an integer, we have an
      overflow only if the number is greater than INT_MAXNUM constant.

      Suppose the number is 9999900.009 and we are on a 32-bit system. This number
      overflows because it is exactly 10 digits long (7 for the integral part and 3
      for the decimal part) and when multiplicating the last digit -- with the
      accumulator technique in `parse_digit.c` -- an overflow occurs, because
      999990000 * 9 is greater than the maximum 32-bit integer 2147483647.

      We then compare the integral part and the decimal part (if present) char by char
      with the INT_MAXNUM constant, and if the comparison shows that at least one char
      is greater than the corresponding char in INT_MAXNUM, then we have an overflow.
    */
    char* integral_maxnum = INT_MAXNUM;
    if (memory_compare(integral_start, integral_maxnum, integral_length) > 0) {
      fail("number overflow");
      goto procedure_failure;
    }
    if (decimal_length > 0) {
      char* decimal_maxnum = integral_maxnum + integral_length;
      if (memory_compare(decimal_start, decimal_maxnum, decimal_length) > 0) {
        fail("number overflow");
        goto procedure_failure;
      }
    }
  }

  if (unlikely(exponent_length > DEC_EXP_MAXCHARS || exponent > DEC_EXP_MAX)) {
    fail("exponent overflow");
    goto procedure_failure;
  }

#ifdef PARSE_NUMBER__INTEGER
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
#ifdef PARSE_NUMBER__INTEGER
  result = (int) number_dec;
#endif
  
#ifdef PARSE_NUMBER__DECIMAL
  result = number_dec;
#endif

  if (negative)
    result = -result;

  goto procedure_success;
#endif
