
  int io_position = io_cursor - io_begin;

  char extraction[64] = { 0 };
  char* extraction_begin;
  char* extraction_end;
  int extraction_size = 0;

  char caret[64] = { 0 };
  int caret_position = 0;

  extraction_begin = io_cursor - 32;
  if (extraction_begin < io_begin)
    extraction_begin = io_begin;

  extraction_end = io_cursor + 32;
  if (extraction_end > io_end)
    extraction_end = io_end;

  extraction_size = extraction_end - extraction_begin;
  if (extraction_size > lengthof(extraction))
    extraction_size = lengthof(extraction);

  byte_copy(extraction, extraction_begin, extraction_size);
  extraction[lengthof(extraction)] = '\0';

  caret_position = io_cursor - extraction_begin;
  for (int i = 0; i < caret_position; i++)
    caret[i] = ' ';
  caret[caret_position] = '^';

  for (int i = 0; i < lengthof(extraction); i++)
    if (extraction[i] == '\n')
      extraction[i] = 92;

  fail("%.*s, at position %li:\n%s\n%s\n",
    sp(failure.message), io_position, extraction, caret);
