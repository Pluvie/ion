static inline struct http_header http_parse_header (
    struct io* io,
    struct memory* allocator
)
{
  io_cursor_save(io);

  struct http_header header = { 0 };

  char* character;
  u64 name_begin = io->cursor;
  u64 value_begin = io->cursor;

read_name:
  character = io_read(io, sizeof(char));
  if (error.occurred)
    return header;

  if (isspace(*character)) {
    fail("no space allowed in header name");
    return header;
  }

  if (*character == ':')
    goto read_separator;

  header.name.length++;
  goto read_name;

read_separator:
  character = io_read(io, sizeof(char));
  if (error.occurred)
    return header;

  if (isspace(*character))
    goto read_separator;

  value_begin = io->cursor - 1;
  header.value.length++;

read_value:
  character = io_read(io, sizeof(char));
  if (error.occurred)
    return header;

  if (*character == '\n')
    goto terminate;

  if (*character == '\r')
    goto read_terminator;

  header.value.length++;
  goto read_value;

read_terminator:
  character = io_read(io, sizeof(char));
  if (error.occurred)
    return header;

  if (*character != '\n') {
    fail("expected line feed after carriage return to end header value");
    return header;
  }

terminate:
  u64 final_cursor_position = io->cursor;

  header.name.content = memory_alloc(allocator, header.name.length + 1);
  header.value.content = memory_alloc(allocator, header.value.length + 1);

  io->cursor = name_begin;
  char* name = io_read(io, header.name.length);
  if (error.occurred)
    return header;

  memcpy(header.name.content, name, header.name.length);
  header.name.content[header.name.length] = '\0';

  io->cursor = value_begin;
  char* value = io_read(io, header.value.length);
  if (error.occurred)
    return header;

  memcpy(header.value.content, value, header.value.length);
  header.value.content[header.value.length] = '\0';

  io_cursor_restore(io);
  io->cursor = final_cursor_position;

  return header;
}
