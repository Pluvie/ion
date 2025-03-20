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
    goto error;

  if (is_httptoken(*character)) {
    header.name.length++;
    goto read_name;
  }

  if (*character == ':')
    goto read_separator;

  fail("header name must be a token: no spaces or delimiters allowed");
  error_add_io_extraction(io);
  goto error;

read_separator:
  character = io_read(io, sizeof(char));
  if (error.occurred)
    goto error;

  if (is_httpwspace(*character))
    goto read_separator;

  value_begin = io->cursor - 1;
  header.value.length++;

read_value:
  character = io_read(io, sizeof(char));
  if (error.occurred)
    goto error;

  /**
   * [RFC 7230](https://www.ietf.org/rfc/rfc7230.txt)
   * Section 3.5 - Message Parsing Robustness
   *
   * Although the line terminator for the start-line and header fields is
   * the sequence CRLF, a recipient MAY recognize a single LF as a line
   * terminator and ignore any preceding CR. */
  if (*character == '\n')
    goto terminate;

  if (*character == '\r')
    goto read_terminator;

  header.value.length++;
  goto read_value;

read_terminator:
  character = io_read(io, sizeof(char));
  if (error.occurred)
    goto error;

  if (*character != '\n') {
    fail("expected line feed after carriage return to end header value");
    error_add_io_extraction(io);
    goto error;
  }

terminate:
  u64 final_cursor_position = io->cursor;

  header.name.content = memory_alloc(allocator, header.name.length + 1);
  header.value.content = memory_alloc(allocator, header.value.length + 1);

  io->cursor = name_begin;
  char* name = io_read(io, header.name.length);
  if (error.occurred)
    goto error;

  memcpy(header.name.content, name, header.name.length);
  header.name.content[header.name.length] = '\0';

  io->cursor = value_begin;
  char* value = io_read(io, header.value.length);
  if (error.occurred)
    goto error;

  memcpy(header.value.content, value, header.value.length);
  header.value.content[header.value.length] = '\0';

  io_cursor_restore(io);
  io->cursor = final_cursor_position;

  return header;

error:
  return (struct http_header) { 0 };
}
