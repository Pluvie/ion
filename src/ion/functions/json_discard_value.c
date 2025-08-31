{
  switch(*io->cursor) {
  case '{':
    return json_discard_object(io);

  case '[':
    return json_discard_array(io);

  default:
    if (json_discard_string(io))
      return;

    if (json_discard_number(io))
      return;

    if (json_discard_bool(io))
      return;

    if (json_discard_null(io))
      return;

    if (failure.occurred)
      return;

    fail("expected a json value");
    return;
  }
}
