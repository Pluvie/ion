
  if (unlikely(*json_cursor(source) != '{')) {
    fail("expected object begin");
    return;
  }

  json_advance(source, 1);

  json_parse_object_init;
  #include "json_parse_spaces.c"

  if (*json_cursor(source) == '}') {
    json_advance(source, 1);
    return;
  }

parse_member:
  #include "json_parse_spaces.c"

  str object_member_name = { 0 };
  #define result object_member_name
  #include "json_parse_string.c"
  #undef result

  json_parse_object_member_name;
  if (unlikely(failure.occurred))
    return;

  #include "json_parse_spaces.c"

  if (unlikely(*json_cursor(source) != ':')) {
    fail("expected colon after object member name");
    return;
  }

  json_advance(source, 1);
  #include "json_parse_spaces.c"

  json_parse_object_member_value;
  if (unlikely(failure.occurred))
    return;

  #include "json_parse_spaces.c"

  switch(*json_cursor(source)) {
  case ',':
    json_advance(source, 1);
    goto parse_member;

  case '}':
    json_advance(source, 1);
    return;

  default:
    fail("expected comma or object end");
  }

  return;
