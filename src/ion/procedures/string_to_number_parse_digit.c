
  do {
#ifndef STRING_TO_NUMBER__DISCARD
    accumulator = (10 * accumulator) + (*cursor - '0');
#endif
    cursor++;
  } while (*cursor >= '0' && *cursor <= '9');
