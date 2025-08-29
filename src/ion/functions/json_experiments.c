void json<T>_parse_string_direct (
    struct io* io,
    T* source,
    string* result
)
{
  int cursor = io_cursor_save(io);
  bool escaped = false;
  char* data;

  data = io_read(io, source, sizeof(char));
  result->pointer = data;

  if (*data != '"')
    goto error;

read_character:
  data = io_read(io, source, sizeof(char));

  if (escaped) {
    escaped = false;
    goto read_character;
  }

  if (*data == 92) {
    escaped = true;
    goto read_character;
  }

  if (*data == '"')
    goto terminate;

  goto read_character;

terminate:
  result->length = io->cursor - cursor;
  return;

error:
  *result = (string) { 0 };
  io_cursor_restore(io, cursor);
  return;
}

void json<T>_parse_spaces_direct (
    struct io* io,
    T* source
)
{
read_space:
  char* data = io_read(io, source, sizeof(char));

  if (isspace(*data))
    goto read_space;

  io->cursor--;
}



bool json<T>_parse_null_direct (
    struct io* io,
    T* source
)
{
  char* data = io_read(io, source, lengthof("null"));

  if (char_compare("null", data, lengthof("null")) == 0)
    return true;

  return false;
}


bool json<T>_parse_bool_direct (
    struct io* io,
    T* source
)
{
  char* data = io_read(io, source, lengthof("false"));

  if (char_compare("true", data, lengthof("true")) == 0)
    return true;

  if (char_compare("false", data, lengthof("false")) == 0)
    return true;

  return false;
}


bool json<T>_parse_number_direct (
    struct io* io,
    T* source
)
{
  int cursor = io->cursor;
  char* data = io_read(io, source, 32);
  char* end;

  strtold(data, &end);
  int number_length = (end - data);

  if (errno == 0) {
    io->cursor = cursor + number_length;
    return true;
  }

  return false;
}



void json<T>_decode_direct (
    struct io* io,
    T* source
)
{
  char* data;
  string result;

  json(parse_spaces_direct, io, source);
  data = io_read(io, source, sizeof(char));
  switch (*data) {
  case '{':
    goto parse_object;

  case '[':
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
    io->cursor--;
    json(parse_number_direct, io, source);
    return;

  default:
    io->cursor--;

    json(parse_string_direct, io, source, &result);
    if (result.length > 0)
      return;

    if (json(parse_null_direct, io, source))
      return;
    if (json(parse_bool_direct, io, source))
      return;

    fail("invalid json value");
    //failure_add_io_info(io);
  }

  return;

parse_object:
  json(parse_spaces_direct, io, source);
  json(parse_string_direct, io, source, &result); // field

  json(parse_spaces_direct, io, source);
  io_read(io, source, sizeof(char)); // colon ':'
  json(parse_spaces_direct, io, source);

  json(decode_direct, io, source); // value
  json(parse_spaces_direct, io, source);

  data = io_read(io, source, sizeof(char));
  if (*data == ',')
    goto parse_object;

  if (*data == '}')
    return;

  fail("bad object end");
  //failure_add_io_info(io);
  return;

parse_array:
  json(parse_spaces_direct, io, source);
  json(decode_direct, io, source); // value
  json(parse_spaces_direct, io, source);

  data = io_read(io, source, sizeof(char));
  if (*data == ',')
    goto parse_array;

  if (*data == ']')
    return;

  fail("bad array end");
  //failure_add_io_info(io);
  return;
}
