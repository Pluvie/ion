
  int number = 0;
  char* begin = io->cursor;

  /* Negative numbers. Just skip the minus. */
  if (*io->cursor == '-')
    io_advance(io, 1);

  if (*io->cursor == '0') {
    /* Numbers starting with 0 and followed by a decimal part. */
    io_advance(io, 1);

    if (likely(*io->cursor == '.'))
      goto parse_decimal;

    goto parse_failure;

  } else if (*io->cursor >= '1' && *io->cursor <= '9') {
    /* All other numbers. */
    #include "json_parse_digit.c"

    if (*io->cursor == '.')
      goto parse_decimal;

    goto parse_success;

  } else {
    /* Not a number. */
    goto parse_failure;
  }

parse_decimal:
  io_advance(io, 1);

  if (*io->cursor >= '0' && *io->cursor <= '9')
    #include "json_parse_digit.c"
  else
    goto parse_failure;

  if (*io->cursor != 'e' && *io->cursor != 'E')
    goto parse_success;

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
  io_cursor_restore(io, begin);
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
  return false;
#endif

parse_success:
#ifndef JSON_DISCARD
  #ifdef JSON_DECODE_INT
    memcpy(target, number, sizeof(int));
  #else
    memcpy(target, (dec) number, sizeof(dec));
  #end
  return;

#else
  return true;
#endif
