
  if (unlikely(*json_cursor(source) != '[')) {
    fail("expected array begin");
    return;
  }

  json_advance(source, 1);
  goto init_callback;

init_resume:
  json_parse_spaces(source);

  if (*json_cursor(source) == ']') {
    json_advance(source, 1);
    return;
  }

next_member:
  json_parse_spaces(source);
  goto member_callback;

member_resume:
  if (unlikely(failure.occurred))
    return;

  json_parse_spaces(source);

  switch(*json_cursor(source)) {
  case ',':
    json_advance(source, 1);
    goto next_member;

  case ']':
    json_advance(source, 1);
    return;

  default:
    fail("expected comma or array end");
  }

  return;
