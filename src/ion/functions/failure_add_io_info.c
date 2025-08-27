void failure_add_io_info (
    struct io* io
)
{
  char extraction[64] = { 0 };
  char caret[64] = { 0 };

  int extraction_size = 0;
  int caret_position = 0;
  int position = 0;

  if (io->buffer.enabled && io->channel != IO_MEMORY)
    goto extract_from_buffer;
  else
    goto extract_from_channel;

extract_from_buffer:
  int buffer_begin = io->buffer.cursor - 32;
  if (buffer_begin < 0)
    buffer_begin = 0;

  int buffer_end = io->buffer.cursor + 32;
  if (buffer_end > io->buffer.data.length)
    buffer_end = io->buffer.data.length;

  extraction_size = buffer_end - buffer_begin;
  if (extraction_size > lengthof(extraction))
    extraction_size = lengthof(extraction);

  byte_copy(extraction, io->buffer.data.pointer + buffer_begin, extraction_size);
  extraction[lengthof(extraction)] = '\0';

  caret_position = 0;
  for (; caret_position < io->buffer.cursor - buffer_begin - 1; caret_position++)
    caret[caret_position] = ' ';
  caret[caret_position] = '^';

  position = io->cursor - (io->buffer.data.length - io->buffer.cursor);

  goto store_message;

extract_from_channel:
  int channel_begin = io->cursor - 32;
  if (io->channel != IO_MEMORY || channel_begin < 0)
    channel_begin = 0;

  int channel_end = io->cursor + 32;
  if (io->channel != IO_MEMORY)
    channel_end = io->result.length;
  else if (channel_end > io->length)
    channel_end = io->length;

  extraction_size = channel_end - channel_begin;
  if (extraction_size > lengthof(extraction))
    extraction_size = lengthof(extraction);

  if (io->channel == IO_MEMORY)
    byte_copy(extraction, io->memory + channel_begin, extraction_size);
  else
    byte_copy(extraction, io->result.pointer + channel_begin, extraction_size);

  extraction[lengthof(extraction)] = '\0';

  caret_position = 0;
  for (; caret_position < io->cursor - channel_begin - 1; caret_position++)
    caret[caret_position] = ' ';
  caret[caret_position] = '^';

  position = io->cursor;

store_message:
  for (int i = 0; i < lengthof(extraction); i++)
    if (extraction[i] == '\n')
      extraction[i] = 92;

  fail("%.*s, at position %li:\n%s\n%s\n",
    sp(failure.message), position, extraction, caret);
}
