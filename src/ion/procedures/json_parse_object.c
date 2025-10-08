
  if (unlikely(*io_cursor(io) != '{')) {
    fail("expected object begin");
    return;
  }

  io_advance(io, 1);

  json_parse_object_init;
  #include "json_parse_spaces.c"

  if (*io_cursor(io) == '}') {
    io_advance(io, 1);
    return;
  }

parse_member:
  #include "json_parse_spaces.c"

  string object_member_name = { 0 };
  #define result object_member_name
  #include "json_parse_string.c"

  json_parse_object_member_name;
  if (unlikely(failure.occurred))
    return;

  #include "json_parse_spaces.c"

  if (unlikely(*io_cursor(io) != ':')) {
    fail("expected colon after object member name");
    return;
  }

  io_advance(io, 1);
  #include "json_parse_spaces.c"

  json_parse_object_member_value;
  if (unlikely(failure.occurred))
    return;

  #include "json_parse_spaces.c"

  switch(*io_cursor(io)) {
  case ',':
    io_advance(io, 1);
    goto parse_member;

  case '}':
    io_advance(io, 1);
    return;

  default:
    fail("expected comma or object end");
  }

  return;
