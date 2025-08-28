static inline void json_decode_struct (
    void* obj,
    struct io* io,
    struct reflection* rfx,
    struct memory* allocator
)
{
  struct reflection* field_rfx = NULL;
  int field_name_length = 0;
  char character;

  json_parse_spaces(io);
  if (unlikely(failure.occurred))
    return;

  io_read(io, sizeof(char));
  if (unlikely(failure.occurred))
    return;

  character = string_char_at(io->result, 0);
  if (character != '{') {
    fail("expected object begin '{'");
    failure_add_io_info(io);
    return;
  }

parse_field:
  json_parse_spaces(io);
  if (unlikely(failure.occurred))
    return;

  /* Parse field name. */
  field_name_length = json_parse_string(io);
  if (unlikely(failure.occurred))
    return;

  if (field_name_length < 0)
    goto check_object_end;

  if (rfx != NULL) {
    string field_name_no_quotes = substring(io->result, 1, -2);
    field_rfx = reflection_field_find(rfx, field_name_no_quotes);

  } else {
    field_rfx = NULL;
  }

  /* Check colon. */
  json_parse_spaces(io);
  if (unlikely(failure.occurred))
    return;

  io_read(io, sizeof(char));
  if (unlikely(failure.occurred))
    return;

  character = string_char_at(io->result, 0);
  if (io->result.length == 0 || character != ':') {
    fail("expected a `:` after the field name");
    failure_add_io_info(io);
    return;
  }

  /* Parse field value. */
  json_parse_spaces(io);
  if (unlikely(failure.occurred))
    return;

  if (field_rfx != NULL) {
    void* field_obj = obj + field_rfx->offset;
    json_decode(field_obj, io, field_rfx, allocator);

  } else {
    json_decode(NULL, io, NULL, NULL);
  }

  if (unlikely(failure.occurred))
    return;

  /* Check comma -- next field --, or object end. */
  json_parse_spaces(io);
  if (unlikely(failure.occurred))
    return;

  io_read(io, sizeof(char));
  if (unlikely(failure.occurred))
    return;

  character = string_char_at(io->result, 0);
  switch (character) {
  case '}':
    goto terminate;

  case ',':
    goto parse_field;

  default:
    fail("expected comma, or object end '}'");
    failure_add_io_info(io);
    return;
  }

check_object_end:
  io_read(io, sizeof(char));
  if (unlikely(failure.occurred))
    return;

  character = string_char_at(io->result, 0);
  if (character != '}') {
    fail("expected an object field, or object end '}'");
    failure_add_io_info(io);
    return;
  }

terminate:
  if (rfx == NULL)
    return;

  reflection_validate(rfx, obj);
  if (unlikely(failure.occurred))
    return failure_add_reflection_info(rfx);
}
