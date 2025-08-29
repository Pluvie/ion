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
  string result_string;
  bool result_bool;

  json(parse_spaces, io, source);
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

    json(parse_string, io, source, &result_string);
    if (result_string.length > 0)
      return;

    if (json(parse_null_direct, io, source))
      return;

    if (json(parse_bool, io, source, &result_bool))
      return;

    fail("invalid json value");
    //failure_add_io_info(io);
  }

  return;

parse_object:
  json(parse_spaces, io, source);
  json(parse_string, io, source, &result_string); // field

  json(parse_spaces, io, source);
  io_read(io, source, sizeof(char)); // colon ':'
  json(parse_spaces, io, source);

  json(decode_direct, io, source); // value
  json(parse_spaces, io, source);

  data = io_read(io, source, sizeof(char));
  if (*data == ',')
    goto parse_object;

  if (*data == '}')
    return;

  fail("bad object end");
  //failure_add_io_info(io);
  return;

parse_array:
  json(parse_spaces, io, source);
  json(decode_direct, io, source); // value
  json(parse_spaces, io, source);

  data = io_read(io, source, sizeof(char));
  if (*data == ',')
    goto parse_array;

  if (*data == ']')
    return;

  fail("bad array end");
  //failure_add_io_info(io);
  return;
}
