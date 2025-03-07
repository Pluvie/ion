static inline void json_decode_struct (
    struct io* io,
    struct reflection* rfx
)
{
  struct reflection* field_rfx = NULL;
  char* field_name = NULL;
  u64 field_name_length = 0;
  u64 field_index = 0;

  char* character;

object_begin:
  json_parse_spaces(io);
  if (error.occurred)
    return;

  character = io_read(io, sizeof(char));
  if (error.occurred)
    return;

  if (*character != '{') {
    fail("expected `{` to begin object");
    error_add_io_extraction(io);
    return;
  }

check_empty_object:
  json_parse_spaces(io);
  if (error.occurred)
    return;

  character = io_peek(io, sizeof(char));
  if (error.occurred)
    return;

  if (*character == '}') {
    io_read(io, sizeof(char));
    if (error.occurred)
      return;

    goto terminate;
  }

  goto parse_field;

next_field:
  json_parse_spaces(io);
  if (error.occurred)
    return;

parse_field:
  field_name_length = json_parse_string(io);
  if (error.occurred)
    return;

  if (field_name_length == 0) {
    fail("expected a string as object key");
    error_add_io_extraction(io);
    return;
  }

read_field:
  field_name = io_read(io, field_name_length);
  if (error.occurred)
    return;

  if (rfx == NULL) {
    field_rfx = NULL;
    goto check_semicolon;
  }

  for vector_each(rfx->fields, struct reflection*, fx) {
    /* Field name equality must be done removing the `"` surrounding `field_name`.*/
    if (strneq(fx->name->content, field_name + 1, field_name_length - 2)) {
      field_rfx = fx;
      goto check_semicolon;
    }
  }

  field_rfx = NULL;

check_semicolon:
  json_parse_spaces(io);
  if (error.occurred)
    return;

  character = io_read(io, sizeof(char));
  if (error.occurred)
    return;

  if (*character != ':') {
    fail("expected a `:` after the field name");
    error_add_io_extraction(io);
    return;
  }

  json_parse_spaces(io);
  if (error.occurred)
    return;

parse_value:
  if (field_rfx != NULL) {
    field_rfx->target = rfx->target + field_rfx->offset;
    json_decode(io, field_rfx);

  } else {
    json_decode(io, NULL);
  }

  if (error.occurred)
    return;

check_comma:
  json_parse_spaces(io);
  if (error.occurred)
    return;

  character = io_read(io, sizeof(char));
  if (error.occurred)
    return;

  switch (*character) {
  case '}':
    goto terminate;

  case ',':
    field_index++;
    goto next_field;

  default:
    fail("expected comma or object end after field value");
    error_add_io_extraction(io);
    return;
  }

terminate:
  if (rfx == NULL)
    return;

  reflection_validate(rfx, rfx->target);
  if (error.occurred)
    return error_add_reflection_path(rfx);
}
