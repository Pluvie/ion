/*
  This procedure is meant to be used only in the `parse_number.c` procedure.
  It parses each character in the cursor, converting it to an integer, using an
  accumulator value.

  This is an optimistic approach to number parsing, aimed at maximizing performance.
  In real world cases, most numbers are relatively small, and even when containing
  a fractional part, they are rarely comprised of more than 10/15 digits, overall.

  If this technique is used, it can greatly improve number parsing speed over
  traditional approaches which are more conservative and prioritize worst-case
  scenarios. If those scenarios should occur while using this optimistic technique,
  fallbacks are put in place in order to resort to a safer, albeit slower, parsing.
*/

  do {
#ifndef PARSE_NUMBER__DISCARD
    accumulator = (10 * accumulator) + (*cursor - '0');
#endif
    cursor++;
  } while (*cursor >= '0' && *cursor <= '9');
