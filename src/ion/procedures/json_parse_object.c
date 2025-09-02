
  if (unlikely(*io->cursor != '{'))
    goto parse_failure;

  io_advance(io, 1);

parse_field:
  #include "json_parse_spaces.c"

#ifndef JSON_DISCARD
  // string* field;
  // json_decode_string(io, &field);
  /* Here logic to find the field in the rfx. */
#else
  if (json_discard_string(io))
    goto parse_colon;

  if (*io->cursor == '}')
    goto parse_success;

  fail("expected an object field or object end");
  goto parse_failure;
#endif

parse_colon:
  #include "json_parse_spaces.c"

  if (*io->cursor == ':') {
    io_advance(io, 1);
    goto parse_value;
  }

  fail("expected colon after object field");
  goto parse_failure;


parse_value:
#ifndef JSON_DISCARD
  // json_decode_value(io, target);
  /* Here logic to decode value. */
#else
  if (json_discard_value(io))
    goto parse_comma_or_end;

  goto parse_failure;
#endif

parse_comma_or_end:
  #include "json_parse_spaces.c"

  switch(*io->cursor) {
  case ',':
    io_advance(io, 1);
    goto parse_field;

  case '}':
    io_advance(io, 1);
    goto parse_success;

  default:
    if (failure.occurred)
      goto parse_failure;

    fail("expected comma or object end");
  }

  goto parse_failure;
