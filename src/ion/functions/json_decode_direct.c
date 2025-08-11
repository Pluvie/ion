void* io_peek_direct (struct io* io) {
  if (unlikely(io->cursor >= io->length))
    return NULL;

  return io->memory + io->cursor;
}



void* io_read_direct (struct io* io, int amount) {
  if (io->cursor + amount > io->length)
    amount = io->length + io->cursor;

  if (unlikely(io->cursor >= io->length))
    return NULL;

  void* data = io->memory + io->cursor;
  io->cursor += amount;
  return data;
}



int json_parse_string_direct(struct io* io) {
  int cursor = io->cursor;
  int length = 0;
  bool escaped = false;
  char* result;

  result = io_read_direct(io, sizeof(char));
  if (result == NULL)
    goto error;

  if (*result != '"')
    goto error;

  length++;

read_character:
  result = io_read_direct(io, sizeof(char));

  if (result == NULL)
    goto error;

  if (escaped) {
    escaped = false;
    length++;
    goto read_character;
  }

  if (*result == 92) {
    escaped = true;
    length++;
    goto read_character;
  }

  if (*result == '"') {
    length++;
    goto terminate;
  }

  length++;
  goto read_character;

terminate:
  return length;

error:
  io->cursor = cursor;
  return -1;
}


void json_parse_spaces_direct (struct io* io) {
  char* result;

read_space:
  result = io_peek_direct(io);
  if (result == NULL)
    return;

  if (isspace(*result)) {
    io_read_direct(io, sizeof(char));
    goto read_space;
  }
}


int json_parse_null_direct (
    struct io* io
)
{
  char* peek = io_peek_direct(io);
  if (peek == NULL)
    return -1;

  if (streq(s("null"), peek))
    return lengthof("null");

  return -1;
}


int json_parse_bool_direct (
    struct io* io
)
{
  char* peek = io_peek_direct(io);
  if (peek == NULL)
    return -1;

  if (streq(s("true"), peek))
    return lengthof("true");

  if (streq(s("false"), peek))
    return lengthof("false"); 

  return -1;
}


dec json_parse_number_direct (struct io* io) {
  char* end;
  char* result = io_peek_direct(io);
  dec number = strtold(result, &end);
  if (errno == 0)
    io->cursor += (end - result);
  return number;
}



void json_decode_direct (
    struct io* io
)
{
  int length;
  char* result;

  json_parse_spaces_direct(io);

  result = io_peek_direct(io);
  switch (*result) {
  case '"':
    length = json_parse_string_direct(io);
    //result = io->memory + (io->cursor - length);
    //print_c(PRINT_COLOR_CYAN, "value [string]: %.*s", (int32) length, result);
    return;

  case '{':
    //print_c(PRINT_COLOR_CYAN, "object begin");
    io_read_direct(io, sizeof(char));
    goto parse_object;

  case '[':
    //print_c(PRINT_COLOR_CYAN, "array begin");
    io_read_direct(io, sizeof(char));
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
    length = json_parse_number_direct(io);
    //result = io->memory + (io->cursor - length);
    //print_c(PRINT_COLOR_CYAN, "value [number]: %.*s", (int32) length, result);
    return;

  default:
    length = json_parse_null_direct(io);
    if (length > 0) {
      //result = io->memory + (io->cursor - length);
      //print_c(PRINT_COLOR_CYAN, "value [null]: %.*s", (int32) length, result);
      return;
    }

    length = json_parse_bool_direct(io);
    if (length > 0) {
      //result = io->memory + (io->cursor - length);
      //print_c(PRINT_COLOR_CYAN, "value [bool]: %.*s", (int32) length, result);
      return;
    }

    fail("invalid json value");
    io_error_extract(io);
  }

  return;

parse_object:
  json_parse_spaces_direct(io);
  length = json_parse_string_direct(io);
  //result = io->memory + (io->cursor - length);
  //print_c(PRINT_COLOR_CYAN, "field [string]: %.*s", (int32) length, result);

  json_parse_spaces_direct(io);
  io_read_direct(io, sizeof(char)); // colon ':'

  json_parse_spaces_direct(io);
  json_decode_direct(io);

  json_parse_spaces_direct(io);
  result = io_read_direct(io, sizeof(char));
  if (*result == ',') {
    //print_c(PRINT_COLOR_GREEN, "next field");
    goto parse_object;
  }

  if (*result == '}')
    return;

  fail("bad object end");
  io_error_extract(io);
  return;

parse_array:
  json_parse_spaces_direct(io);
  json_decode_direct(io);
  json_parse_spaces_direct(io);

  result = io_read_direct(io, sizeof(char));
  if (*result == ',') {
    //print_c(PRINT_COLOR_GREEN, "next value");
    goto parse_array;
  }

  if (*result == ']')
    return;

  fail("bad array end");
  io_error_extract(io);
  return;
}
