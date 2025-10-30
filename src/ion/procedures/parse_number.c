/* This procedure contains the number parsing logic for both integers and decimals,
  written in base 10.

  These are the procedure prerequisites on local variables:

    - `source` must be a `str*`: it must point to the number to be parsed. Warning: the
      source shall be consumed! If you don't want that, pass a copy to this pointer.

  The procedure recognizes numbers in the following format, which is locale independent:

    - The number must start with a minus `-` sign or with at least one digit `[0-9]+`.
    - The number may be followed by a decimal separator `.`. If this is the case, the
      separator must be followed by at least one digit `[0-9]+`.
    - The number may be followed by an exponent `e` or `E`. If this is the case, the
      exponent letter must be followed by at least one digit `[0-9]+` optionally
      preceded by a sign `-` or `+`.

  The procedure shall look for these constants, and trigger some specific behaviour
  if they are defined:

    - `PARSE_NUMBER__SAFE`: if this constant is defined, the parsing shall always check
      if the source does not exceed its length. This type of parsing is inherently
      slower, but safe. When it is known that the source has at least one padding
      character at the end -- meaning that the last character of the string is not the
      last valid character of the number to parse -- then it is possible to avoid
      defining this constant to speed up the parsing.
    - `PARSE_NUMBER__DISCARD`: if this constant is defined, then the parsing shall
      complete its execution but no result shall be given. This optimizes performance
      when the input must be consumed but the parsing result is not necessary.
    - `PARSE_NUMBER__INTEGER`: if this constant is defined, the parsing shall
      return an integer on the `result` local variable -- which must be an `int`.
      If the number had any fractional part, it shall be discarded. If the number
      had an exponent, it shall be calculated and any resulting fractional part shall
      be discarded.
    - `PARSE_NUMBER__DECIMAL`: if this constant is defined, the parsing shall
      return a decimal on the `result` local variable -- which must be a `dec`. */

  char* cursor_begin = source->chars;
#define cursor source->chars

#ifdef PARSE_NUMBER__SAFE
  /* When parsing safely, each advancement is checked against the source length. If,
    at any point, this is length is surpassed, the parsing shall return the error code
    `Parse_Number_Exhausted` and the result shall be undefined. */
  uint source_pos = 0;
#define cursor_advance                \
  if (source_pos++ <= source->length) \
    source->chars++;                  \
  else                                \
    return Parse_Number_Exhausted

#else
  /* When parsing for speed, assumes that there is always a valid character after the
    number which is *not* a valid part of the number. This character, when encountered,
    shall terminate the parsing. */
#define cursor_advance \
  source->chars++
#endif

#ifndef PARSE_NUMBER__DISCARD
  /* When not discarding, it must store all partial results of elaboration. */
  int number = 0;
  int exponent = 0;
  int exponent_offset = 0;
  int accumulator = 0;
  bool negative = false;
  bool negative_exponent = false;

  int integral_length = 0;
  int decimal_length = 0;
  int exponent_length = 0;
  int number_length = 0;

  char* integral_start = cursor;
  char* decimal_start = nullptr;
  char* exponent_start = nullptr;

#if   defined(PARSE_NUMBER__INTEGER)
  int result_int = 0;
#elif defined(PARSE_NUMBER__DECIMAL)
  dec result_dec = 0;
#endif
#endif

  /* Number starts with 1-9. Go parse the integral part. */
  if (*cursor >= '1' && *cursor <= '9')
    goto parse_integral;

  /* Number starts with 0. Skip any other 0 afterwards. */
  if (*cursor == '0') {
    do { cursor_advance; } while (*cursor == '0');

    if (*cursor == '.')
      goto parse_decimal;
    else if (*cursor >= '1' && *cursor <= '9')
      goto parse_integral;
    else
      goto parse_success;
  }

  /* Number does not start with 0-9 and neither with '-': it's not valid. */
  if (*cursor != '-')
    goto parse_failure;

  /* Number starts with '-'. Advances the cursor and, if not discarding, remembers
    that it was negative in order to change its sign at the end. Then proceeds to
    parse the integral part.  */
  cursor_advance;
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
  cursor_advance; /* Advances over the '.'. */
#ifdef PARSE_NUMBER__DECIMAL
  decimal_start = cursor;
#endif

  if (*cursor >= '0' && *cursor <= '9')
#ifdef PARSE_NUMBER__DECIMAL
    #include "parse_digit.c"
#else
    do { cursor_advance; } while (*cursor >= '0' && *cursor <= '9');
#endif
  else
    goto parse_failure;

#ifndef PARSE_NUMBER__DISCARD
  number = accumulator;
#endif
#ifdef PARSE_NUMBER__DECIMAL
  decimal_length = cursor - decimal_start;
#endif

  if (*cursor != 'e' && *cursor != 'E')
    goto parse_success;


parse_exponent:
  cursor_advance; /* Advances over the 'e' or 'E'. */

  if (*cursor == '-') {
    cursor_advance;
#ifndef PARSE_NUMBER__DISCARD
    negative_exponent = true;
#endif
  } else if (*cursor == '+') {
    cursor_advance;
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
  if (source->chars == cursor_begin)
    return Parse_Number_Empty;
  else
    return Parse_Number_Invalid;


parse_success:
#ifdef PARSE_NUMBER__DISCARD
  return Parse_Number_Success;
#endif

  if (number == 0)
    goto convert_result;

  if (negative_exponent)
    exponent = -exponent;

  exponent_offset = exponent - decimal_length;
  number_length = integral_length + decimal_length;

  #include "parse_number_overflow_checks.c"

#ifdef PARSE_NUMBER__INTEGER
  if (exponent_offset == 0)
    result_int = number;
  else if (exponent_offset < 0)
    result_int = number / (int) powers_of_ten[-exponent_offset];
  else
    result_int = number * (int) powers_of_ten[exponent_offset];
#endif

#ifdef PARSE_NUMBER__DECIMAL
  if (exponent_offset == 0)
    result_dec = (dec) number;
  else if (exponent_offset < 0)
    result_dec = (dec) number / powers_of_ten[-exponent_offset];
  else
    result_dec = (dec) number * powers_of_ten[exponent_offset];
#endif

convert_result:
#ifdef PARSE_NUMBER__INTEGER
  if (negative)
    result_int = -result_int;

  *result = result_int;
#endif
#ifdef PARSE_NUMBER__DECIMAL
  if (negative)
    result_dec = -result_dec;

  *result = result_dec;
#endif
  return Parse_Number_Success;

#undef  PARSE_NUMBER__DISCARD
#undef  PARSE_NUMBER__DECIMAL
#undef  PARSE_NUMBER__INTEGER
#undef  source_advance
#undef  source_char
