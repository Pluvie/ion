void hexdump (
    byte* data,
    u64 length
)
{
  byte hex = 0;
  char ascii = 0;

  u32 groups = length / 8;
  if (length % 8 > 0)
    groups++;

  for (u32 group = 0; group < groups; group++) {
    fprintf(stderr, "| ");
    for (u32 index = group * 8; index < (group * 8) + 8; index++) {
      if (index >= length) {
        fprintf(stderr, "   ");
        continue;
      }
      hex = data[index];
      fprintf(stderr, "%02x ", hex);
    }
    fprintf(stderr, "| ");
    for (u32 index = group * 8; index < (group * 8) + 8; index++) {
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
