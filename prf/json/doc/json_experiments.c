void* io_peek_direct (struct io* io) {
  if (unlikely(io->cursor >= io->length))
    return NULL;

  return io->memory + io->cursor;
}



static inline void* io_channel_read_direct (struct io* io, int amount, void* address) {
  switch (io->channel) {
  case IO_MEMORY:
    if (unlikely(io->cursor + amount > io->length))
      amount = io->length - io->cursor;

    if (unlikely(amount <= 0))
      return NULL;

    void* data = io->memory + io->cursor;
    io_cursor_advance(io, amount);
    return data;

  default:
    fail("not implemented");
  }

  return NULL;
}

static inline void* io_channel_memory_read_direct (struct io* io, int amount) {
  if (io->cursor + amount > io->length)
    amount = io->length + io->cursor;

  if (unlikely(io->cursor >= io->length))
    return NULL;

  void* data = io->memory + io->cursor;
  io_cursor_advance(io, amount);
  return data;
}



void* io_read_direct (struct io* io, int amount) {
  /**
   * Two pieces of code.
   * The first one reads directly from memory.
   * The second one checks whether the io is buffered and which channel it has, then
   * it reads from the corresponding channel.
   *
   * Since the `io_read_direct` function is called a gazillion of times, paying the
   * cost of checking every tims whether the io is buffered and which channel it has
   * -- which are always the same!! -- adds up, and in the end the first block takes
   * ~1.90s while the second ~2.70s.
   *
   * Quite a lot of time! This is what they mean that `if` statements are expensive!
   * Even with branch prediction. */

  /* PIECE 1 */
  return io_channel_memory_read_direct(io, amount);

  /* PIECE 2 */
  /*
  if (io->buffer.enabled) {
    io_buffer_read(io, amount);
    return io->result.pointer;
  }

  if (io->channel == IO_MEMORY)
    return io_channel_memory_read_direct(io, amount);

  alloc_release(io->result.pointer);
  io->result.pointer = alloc_zero(amount);
  return io_channel_read_direct(io, amount, io->result.pointer);
  */
}



int json_parse_string_direct (struct io* io) {
  int cursor = io->cursor;
  int length = 0;
  bool escaped = false;
  char* result;

  result = io_read_direct(io, sizeof(char));

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

  if (eq(peek, "null"))
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

  if (eq(peek, "true"))
    return lengthof("true");

  if (eq(peek, "false"))
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
    failure_add_io_info(io);
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
  failure_add_io_info(io);
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
  failure_add_io_info(io);
  return;
}
