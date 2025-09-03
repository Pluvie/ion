
#ifndef JSON_DISCARD
  int number = 0;
  //int exponent = 0;
  int accumulator = 0;
  bool negative = false;
#endif
  char* begin = io->cursor;

  int integral_length = 0;
#ifdef JSON_DECODE_DEC
  int decimal_length = 0;
  char* decimal_start = io->cursor;
#endif
  char* integral_start = io->cursor;

  /* Number starts with 0-9. Go parse the integral part. */
  if (*io->cursor >= '0' && *io->cursor <= '9')
    goto parse_integral;

  /* Number does not start with 0-9 and neither with '-'.
   * It's not a valid JSON number. */
  if (*io->cursor != '-')
    goto parse_failure;

  /* Number starts with '-'. Advances the I/O and, if not discarding, remembers that
   * it was negative and change its sign at the end. Then proceeds to parse the
   * integral part. */
  io_advance(io, 1);
  integral_start++;
#ifndef JSON_DISCARD
  negative = true;
#endif
  goto parse_integral;


parse_integral:
  #include "json_parse_digit.c"

  integral_length = io->cursor - integral_start;
  /* Non-numbers or numbers starting with 0 and with any other digit afterwards. */
  if (integral_length == 0 || (*integral_start == '0' && integral_length > 1))
    goto parse_failure;

  if (*io->cursor == '.')
    goto parse_decimal;
  else if (*io->cursor == 'e' || *io->cursor == 'E')
    goto parse_exponent;

  goto parse_success;


parse_decimal:
  io_advance(io, 1);
#ifdef JSON_DECODE_DEC
  decimal_start = io->cursor;
#endif

#ifdef JSON_DECODE_INT
  /* If we're decoding an INT, we can memorize the parsed number so far and completely
   * truncate the decimal part when converting. */
  number = accumulator;
  accumulator = 0;
#endif

#ifdef JSON_DECODE_DEC
  decimal_length = io->cursor - decimal_start;
#endif
  if (*io->cursor >= '0' && *io->cursor <= '9')
    #include "json_parse_digit.c"
  else
    goto parse_failure;

#ifdef JSON_DECODE_DEC
  /* If we're decoding a DEC, we memorize the parsed number so far, and start using
   * the accumulator to parse the exponent. It shall be used at the end when
   * converting. */
  number = accumulator;
  accumulator = 0;
#endif

  if (*io->cursor != 'e' && *io->cursor != 'E')
    goto parse_success;

parse_exponent:
  io_advance(io, 1);
  if (*io->cursor == '+' || *io->cursor == '-')
    io_advance(io, 1);

  if (*io->cursor >= '0' && *io->cursor <= '9') {
    #include "json_parse_digit.c"
    goto parse_success;

  } else {
    goto parse_failure;
  }

parse_failure:
#ifndef JSON_DISCARD
  zero_out(target, rfx->size);

  if (unlikely(failure.occurred)) {
    /* Some I/O failure occurred. Nothing to add. */

  } else if (io->cursor > begin) {
    fail("invalid number");

  } else {
    io_cursor_restore(io, begin);
    fail("expected a number");
  }

  failure_add_io_info(io);
  failure_add_reflection_info(rfx);
  return;

#else
  io_cursor_restore(io, begin);
  return false;
#endif

parse_success:
#ifndef JSON_DISCARD
#ifdef JSON_DECODE_INT
  memcpy(target, &number, sizeof(int));
#endif
#ifdef JSON_DECODE_DEC
  dec number_dec = 0;
  if (decimal_length > 0)
    number_dec = number / (10.0 * decimal_length);
  if (negative)
    number_dec = -number_dec;

  memcpy(target, &number_dec, sizeof(dec));
#endif
  return;

#else
  return true;
#endif
