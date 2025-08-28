bool json_parse_string_direct (
    struct io* io,
    T* source
)
{
  char* result;
  int cursor = io->cursor;
  bool escaped = false;

  result = io_read(io, source, sizeof(char));

  if (*result != '"')
    goto error;

read_character:
  result = io_read(io, source, sizeof(char));

  if (escaped) {
    escaped = false;
    goto read_character;
  }

  if (*result == 92) {
    escaped = true;
    goto read_character;
  }

  if (*result == '"')
    goto terminate;

  goto read_character;

terminate:
  return true;

error:
  io->cursor = cursor;
  return false;
}

void json_parse_spaces_direct (
    struct io* io,
    T* source
)
{
read_space:
  char* result = io_read(io, source, sizeof(char));

  if (isspace(*result))
    goto read_space;

  io->cursor--;
}



bool json_parse_null_direct (
    struct io* io,
    T* source
)
{
  char* result = io_read(io, source, lengthof("null"));

  if (char_compare("null", result, lengthof("null")) == 0)
    return true;

  return false;
}


bool json_parse_bool_direct (
    struct io* io,
    T* source
)
{
  char* result = io_read(io, source, lengthof("false"));

  if (char_compare("true", result, lengthof("true")) == 0)
    return true;

  if (char_compare("false", result, lengthof("false")) == 0)
    return true;

  return false;
}


bool json_parse_number_direct (
    struct io* io,
    T* source
)
{
  int cursor = io->cursor;
  char* result = io_read(io, source, 32);
  char* end;

  strtold(result, &end);
  int number_length = (end - result);

  if (errno == 0) {
    io->cursor = cursor + number_length;
    return true;
  }

  return false;
}



void json_decode_direct (
    struct io* io,
    T* source
)
{
  char* result;

  json_parse_spaces_direct(io, source);
  result = io_read(io, source, sizeof(char));
  switch (*result) {
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
    json_parse_number_direct(io, source);
    return;

  default:
    io->cursor--;

    if (json_parse_string_direct(io, source))
      return;
    if (json_parse_null_direct(io, source))
      return;
    if (json_parse_bool_direct(io, source))
      return;

    fail("invalid json value");
    //failure_add_io_info(io);
  }

  return;

parse_object:
  json_parse_spaces_direct(io, source);
  json_parse_string_direct(io, source); // field

  json_parse_spaces_direct(io, source);
  io_read(io, source, sizeof(char)); // colon ':'
  json_parse_spaces_direct(io, source);

  json_decode_direct(io, source); // value
  json_parse_spaces_direct(io, source);

  result = io_read(io, source, sizeof(char));
  if (*result == ',')
    goto parse_object;

  if (*result == '}')
    return;

  fail("bad object end");
  //failure_add_io_info(io);
  return;

parse_array:
  json_parse_spaces_direct(io, source);
  json_decode_direct(io, source); // value
  json_parse_spaces_direct(io, source);

  result = io_read(io, source, sizeof(char));
  if (*result == ',')
    goto parse_array;

  if (*result == ']')
    return;

  fail("bad array end");
  //failure_add_io_info(io);
  return;
}

#undef T
