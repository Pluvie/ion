static inline void json_decode_struct (
    void* obj,
    struct io* io,
    struct reflection* rfx,
    struct memory* allocator
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
    goto check_colon;
  }

  struct string field_name_no_quotes = {
    .content = field_name + 1,
    .length = field_name_length - 2
  };

  field_rfx = reflection_field_find(rfx, &field_name_no_quotes);
  if (field_rfx != NULL)
    goto check_colon;

check_colon:
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
    void* field_obj = obj + field_rfx->offset;
    json_decode(field_obj, io, field_rfx, allocator);

  } else {
    json_decode(NULL, io, NULL, NULL);
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

  reflection_validate(rfx, obj);
  if (error.occurred)
    return error_add_reflection_path(rfx);
}
