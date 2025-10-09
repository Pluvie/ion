
  if (unlikely(*json_cursor(source) != '[')) {
    fail("expected array begin");
    return;
  }

  json_advance(source, 1);

  json_parse_array_init;
  #include "json_parse_spaces.c"

  if (*json_cursor(source) == ']') {
    json_advance(source, 1);
    return;
  }

parse_member:
  #include "json_parse_spaces.c"

  json_parse_array_member;
  if (unlikely(failure.occurred))
    return;

  #include "json_parse_spaces.c"

  switch(*json_cursor(source)) {
  case ',':
    json_advance(source, 1);
    goto parse_member;

  case ']':
    json_advance(source, 1);
    return;

  default:
    fail("expected comma or array end");
  }

  return;
