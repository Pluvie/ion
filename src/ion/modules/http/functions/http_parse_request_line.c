static inline struct http_request http_parse_request_line (
    struct io* io
)
{
  /**
   * [RFC 7230](https://www.ietf.org/rfc/rfc7230.txt)
   * Section 3.1.1 - Request Line
   *
   * A request-line begins with a method token, followed by a single space
   * (SP), the request-target, another single space (SP), the protocol
   * version, and ends with CRLF.
   *
   *   request-line   = method SP request-target SP HTTP-version CRLF
   *
   * The method token indicates the request method to be performed on the
   * target resource.  The request method is case-sensitive.
   *
   *   method         = token
   */

  io_cursor_save(io);

  struct http_request req = { 0 };

  char* character;
  u64 method_begin = io->cursor;
  u64 target_begin = io->cursor;
  u64 version_begin = io->cursor;

read_method:
  character = io_read(io, sizeof(char));
  if (error.occurred)
    goto error;

  if (is_httptoken(*character)) {
    header.name.length++;
    goto read_method;
  }

  if (*character == ' ') {
    target_begin = io->cursor;
    goto read_target;
  }

  fail("HTTP method must be a token: no spaces or delimiters allowed");
  error_add_io_extraction(io);
  goto error;

read_target:
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
  return (struct http_request) { 0 };
}
