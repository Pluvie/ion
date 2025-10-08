
  if (unlikely(*io_cursor(io) != '[')) {
    fail("expected array begin");
    return;
  }

  io_advance(io, 1);

  json_parse_array_init;
  #include "json_parse_spaces.c"

  if (*io_cursor(io) == ']') {
    io_advance(io, 1);
    return;
  }

parse_member:
  #include "json_parse_spaces.c"

  json_parse_array_member;
  if (unlikely(failure.occurred))
    return;

  #include "json_parse_spaces.c"

  switch(*io_cursor(io)) {
  case ',':
    io_advance(io, 1);
    goto parse_member;

  case ']':
    io_advance(io, 1);
    return;

  default:
    fail("expected comma or array end");
  }

  return;
