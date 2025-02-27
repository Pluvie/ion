static inline void error_add_io_extraction (
    struct io* io
)
{
  char extraction[64] = { 0 };
  char caret[64] = { 0 };

  char message[sizeof(error.message)];
  u64 initial_cursor_position = io->cursor;

set_extraction_limits:
  u64 extraction_begin = 0;
  if (initial_cursor_position > 20)
    extraction_begin = initial_cursor_position - 20;

  u64 extraction_end = initial_cursor_position + 20;
  if (extraction_end > io->length)
    extraction_end = io->length;

  u64 extraction_length = extraction_end - extraction_begin;

rewind_cursor:
  io->cursor = extraction_begin;

extract:
  error.occurred = false;
  char* extracted_data = io_read(io, extraction_length);
  if (error.occurred)
    return;

  memcpy(extraction, extracted_data, extraction_length);
  u64 extraction_position = initial_cursor_position - extraction_begin;
  for (u64 i = extraction_position; i < extraction_length; i++)
    if (extraction[i] == '\n')
      extraction[i] = '\0';

  u64 first_newline = 0;
  for (i64 i = extraction_position; i >= 0; i--)
    if (extraction[i] == '\n') {
      first_newline = i;
      break;
    }

  u64 caret_position = extraction_position - first_newline;
  if (caret_position > 0)
    caret_position--;

set_error:
  memset(caret, ' ', caret_position);
  caret[caret_position] = '^';
  caret[caret_position + 1] = '\0';

  error.occurred = true;
  error.length = snprintf(message, sizeof(message),
    "%s, at position %li:\n%s\n%s",
    error.message, initial_cursor_position, extraction, caret);
  memcpy(error.message, message, sizeof(message));

restore_cursor:
  io->cursor = initial_cursor_position;
}
