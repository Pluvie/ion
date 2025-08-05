static inline void json_decode_struct (
    void* obj,
    struct io* io,
    struct reflection* rfx,
    struct memory* allocator
)
{
  struct reflection* field_rfx = NULL;
  int field_name_length = 0;
  slice result;

  #define character ((char*) result.data)[0]

  json_parse_spaces(io);
  if (error.occurred)
    return;

  result = io_read(io, sizeof(char));
  if (error.occurred)
    return;

  if (result.length == 0)
    return;

  if (character != '{') {
    fail("expected object begin '{'");
    io_error_extract(io);
    return;
  }

parse_field:
  json_parse_spaces(io);
  if (error.occurred)
    return;

  field_name_length = json_parse_string(io);
  if (error.occurred)
    return;

  if (field_name_length == 0)
    goto check_object_end;

  result = io_read(io, field_name_length);
  if (error.occurred)
    return;

  if (rfx == NULL) {
    field_rfx = NULL;
    goto check_colon;
  }

  string field_name_no_quotes = { result.data + 1, result.length - 2 };
  field_rfx = reflection_field_find(rfx, &field_name_no_quotes);
  if (field_rfx != NULL)
    goto check_colon;

check_colon:
  json_parse_spaces(io);
  if (error.occurred)
    return;

  result = io_read(io, sizeof(char));
  if (error.occurred)
    return;

  if (result.length == 0)
    return;

  if (character != ':') {
    fail("expected a `:` after the field name");
    io_error_extract(io);
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

  result = io_read(io, sizeof(char));
  if (error.occurred)
    return;

  if (result.length == 0)
    return;

  switch (*character) {
  case '}':
    goto terminate;

  case ',':
    goto parse_field;

  default:
    fail("expected comma, or object end '}'");
    io_error_extract(io);
    return;
  }

check_object_end:
  character = io_read(io, sizeof(char));
  if (error.occurred)
    return;

  if (result.length == 0 || character != '}')
    fail("expected an object field, or object end '}'");
    io_error_extract(io);
    return;
  }


terminate:
  if (rfx == NULL)
    return;

  reflection_validate(rfx, obj);
  if (error.occurred)
    return error_add_reflection_path(rfx);

  #undef character
}
