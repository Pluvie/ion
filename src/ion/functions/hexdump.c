void hexdump (
    void* generic_data,
    int length
)
{
  char* data = generic_data;
  char ascii = 0;
  unsigned char hex = 0;

  int line_length = 8;
  int groups = length / line_length;

  if (length % line_length > 0)
    groups++;

  for (int group = 0; group < groups; group++) {
    fprintf(stderr, "| ");
    for (int index = group * line_length;
        index < (group * line_length) + line_length;
        index++) {
      if (index >= length) {
        fprintf(stderr, "   ");
        continue;
      }
      hex = data[index];
      fprintf(stderr, "%02x ", hex);
    }
    fprintf(stderr, "| ");
    for (int index = group * line_length;
        index < (group * line_length) + line_length;
        index++) {
      if (index >= length) {
        fprintf(stderr, "  ");
        continue;
      }
      ascii = data[index];

/**
 * NOTE(Pluvie): this ugly hack is required because <ctype.h> does not use standard
 * int types but instead typecasts directly the `ascii` argument to an
 * `unsigned short int` (see /usr/include/ctype.h:88).
 *
 * Since we are defaulting `int` to a 64bit signed integer, the `isprint` macro expands
 * to `(unsigned short i64) ascii` which is not a valid expression.
 *
 * We thus restore the original int type for just this expression. */
#undef int
#undef int32
      fprintf(stderr, "%c ", isprint(ascii) ? ascii : '_');
    }
    fprintf(stderr, "|\n");
  }
}

/**
 * NOTE(Pluvie): after the ugly hack above, we can restore our desired `int` type. */
#include "ion/types/int.h"
