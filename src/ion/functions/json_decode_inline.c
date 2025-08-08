void json_decode_inline (
    struct io* io
)
{
  int length;
  slice result;
  #define character ((char*) result.data)[0]

  json_parse_spaces(io);

  result = io_peek(io, sizeof(char));
  switch (character) {
  case '"':
    length = json_parse_string(io);
    result = io_read(io, length);
    //print("value [string]: %.*s", (int32) result.length, (char*) result.data);
    return;

  case '{':
    //print("object begin");
    io_read(io, sizeof(char));
    goto parse_object;

  case '[':
    //print("array begin");
    io_read(io, sizeof(char));
    goto parse_array;

  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
  case '-':
    length = json_parse_number(io);
    result = io_read(io, length);
    //print("value [number]: %.*s", (int32) result.length, (char*) result.data);
    return;

  default:
    length = json_parse_null(io);
    if (length > 0) {
      result = io_read(io, length);
      //print("value [null]: %.*s", (int32) result.length, (char*) result.data);
      return;
    }

    length = json_parse_bool(io);
    if (length > 0) {
      result = io_read(io, length);
      //print("value [bool]: %.*s", (int32) result.length, (char*) result.data);
      return;
    }

    fail("invalid json value");
    io_error_extract(io);
  }

  return;

parse_object:
  json_parse_spaces(io);
  length = json_parse_string(io);
  result = io_read(io, length);
  //print("field [string]: %.*s", (int32) result.length, (char*) result.data);
  //if (length < 0) {
  //  fail("expected string as object key");
  //  io_error_extract(io);
  //  return;
  //}

  json_parse_spaces(io);
  io_read(io, sizeof(char));
  //if (character != ':') {
  //  fail("expected colon after object key");
  //  io_error_extract(io);
  //  return;
  //}

  json_parse_spaces(io);
  json_decode_inline(io);

  json_parse_spaces(io);
  result = io_read(io, sizeof(char));
  if (character == ',') {
    //print("next field");
    goto parse_object;
  }

  if (character == '}')
    return;

  fail("bad object end");
  io_error_extract(io);
  return;

parse_array:
  json_parse_spaces(io);
  json_decode_inline(io);
  json_parse_spaces(io);

  result = io_read(io, sizeof(char));
  if (character == ',') {
    //print("next value");
    goto parse_array;
  }

  if (character == ']')
    return;

  fail("bad array end");
  io_error_extract(io);
  return;

  #undef character
}
