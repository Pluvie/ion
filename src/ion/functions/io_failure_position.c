static inline void io_failure_position (
    struct io* io,
    char* file,
    u64 line
)
{
  u64 position = io->cursor;

  if (io->channel == IO_CHANNEL_SOCK)
    goto set_position_only;
  if (!(io->mode & IO_MODE_READ))
    goto set_position_only;

  goto set_position_with_extraction;

set_position_only:
  fail("%s, at position %li", error.message, position);
  error.trace[error.trace_count - 1].file = file;
  error.trace[error.trace_count - 1].line = line;

  return;

set_position_with_extraction:
  char extraction[64] = { 0 };
  char caret[64] = { 0 };

  u64 extraction_begin = 0;
  if (position > 20)
    extraction_begin = position - 20;

  u64 extraction_end = position + 20;
  if (extraction_end > io->length)
    extraction_end = io->length;

  u64 extraction_length = extraction_end - extraction_begin;

rewind_cursor:
  switch (io->channel) {
  case IO_CHANNEL_MEM:
    io->cursor = extraction_begin;
    break;
  case IO_CHANNEL_FILE:
    fseek(io->file, extraction_begin, SEEK_SET);
    break;
  default:
    return;
  }

extract:
  error.occurred = false;
  io_peek(io, extraction, extraction_length);
  if (error.occurred)
    return;

  extraction[extraction_length] = '\0';

  u64 extraction_position = position - extraction_begin;
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

  fail("%s, at position %li:\n%s\n%s", error.message, position, extraction, caret);
  error.trace[error.trace_count - 1].file = file;
  error.trace[error.trace_count - 1].line = line;

restore_cursor:
  switch (io->channel) {
  case IO_CHANNEL_MEM:
    io->cursor = position;
    return;
  case IO_CHANNEL_FILE:
    fseek(io->file, position, SEEK_SET);
    return;
  default:
    return;
  }
}
