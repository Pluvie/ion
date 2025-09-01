
  if (unlikely(*io->cursor != '['))
    goto parse_error;

  io_advance(io, 1);

parse_value:
  #include "json_parse_spaces.c"

#ifndef JSON_DISCARD
  // json_decode_value(io, target);
  /* Here logic to decode value. */
#else
  if (json_discard_value(io))
    goto parse_comma_or_end;

  if (*io->cursor == ']')
    goto parse_success;

  fail("expected an array element or array end");
  goto parse_error;
#endif

parse_comma_or_end:
  #include "json_parse_spaces.c"

  switch(*io->cursor) {
  case ',':
    goto parse_value;

  case ']':
    io_advance(io, 1);
    goto parse_success;

  default:
    if (failure.occurred)
      goto parse_error;

    fail("expected comma or array end");
  }

  goto parse_error;
