
  if (unlikely(*json_cursor(source) != '{')) {
    fail("expected object begin");
    return;
  }

  json_advance(source, 1);
  goto init_callback;

init_resume:
  json_parse_spaces(source);

  if (*json_cursor(source) == '}') {
    json_advance(source, 1);
    return;
  }

next_member:
  json_parse_spaces(source);

  str object_member_name = { 0 };
  #define result object_member_name
  #include "json_parse_string.c"
  #undef result
  goto member_key_callback;

member_key_resume:
  if (unlikely(failure.occurred))
    return;

  json_parse_spaces(source);

  if (unlikely(*json_cursor(source) != ':')) {
    fail("expected colon after object member name");
    return;
  }

  json_advance(source, 1);
  json_parse_spaces(source);
  goto member_value_callback;

member_value_resume:
  if (unlikely(failure.occurred))
    return;

  json_parse_spaces(source);

  switch(*json_cursor(source)) {
  case ',':
    json_advance(source, 1);
    goto next_member;

  case '}':
    json_advance(source, 1);
    return;

  default:
    fail("expected comma or object end");
  }

  return;
