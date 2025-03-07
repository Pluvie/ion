void hexdump (
    void* generic_data,
    u64 length
)
{
  byte* data = generic_data;
  byte hex = 0;
  char ascii = 0;

  u32 line_length = 8;
  u32 groups = length / line_length;

  if (length % line_length > 0)
    groups++;

  for (u32 group = 0; group < groups; group++) {
    fprintf(stderr, "| ");
    for (u32 index = group * line_length;
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
    for (u32 index = group * line_length;
        index < (group * line_length) + line_length;
        index++) {
      if (index >= length) {
        fprintf(stderr, "  ");
        continue;
      }
      ascii = (char) data[index];
      fprintf(stderr, "%c ", isprint(ascii) ? ascii : '_');
    }
    fprintf(stderr, "|\n");
  }
}
