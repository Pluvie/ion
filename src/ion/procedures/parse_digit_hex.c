/* This procedure is meant to be used only in the `parse_number.c` procedure.
  It parses each character in the cursor, converting it to an integer, using an
  accumulator value. */

  do {
#ifndef PARSE_NUMBER__DISCARD
    switch (*cursor) {
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
      accumulator = (16 * accumulator) + (*cursor - '0');
      break;
    case 'A':
    case 'B':
    case 'C':
    case 'D':
    case 'E':
    case 'F':
      accumulator = (16 * accumulator) + (10 + (*cursor - 'A'));
      break;
    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f':
      accumulator = (16 * accumulator) + (10 + (*cursor - 'a'));
      break;
    }
#endif
    cursor_advance;

  } while ((*cursor >= '0' && *cursor <= '9') ||
           (*cursor >= 'A' && *cursor <= 'F') ||
           (*cursor >= 'a' && *cursor <= 'f'));
