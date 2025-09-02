
  if (unlikely(*io->cursor != '['))
    goto parse_failure;

  io_advance(io, 1);

parse_value:
#ifndef JSON_DISCARD
  // json_decode_value(io, target);
  /* Here logic to decode value. */
#else
  if (json_discard_value(io))
    goto parse_comma_or_end;

  if (*io->cursor == ']') {
    io_advance(io, 1);
    goto parse_success;
  }

  fail("expected an array element or array end");
  goto parse_failure;
#endif

parse_comma_or_end:
  #include "json_parse_spaces.c"

  switch(*io->cursor) {
  case ',':
    io_advance(io, 1);
    goto parse_value;

  case ']':
    io_advance(io, 1);
    goto parse_success;

  default:
    if (failure.occurred)
      goto parse_failure;

    fail("expected comma or array end");
  }

  goto parse_failure;
