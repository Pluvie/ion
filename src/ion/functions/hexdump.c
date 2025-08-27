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
    stream_print(&stderr, "| ");
    for (int index = group * line_length;
        index < (group * line_length) + line_length;
        index++) {
      if (index >= length) {
        stream_print(&stderr, "   ");
        continue;
      }
      hex = data[index];
      stream_print(&stderr, "%02x ", hex);
    }
    stream_print(&stderr, "| ");
    for (int index = group * line_length;
        index < (group * line_length) + line_length;
        index++) {
      if (index >= length) {
        stream_print(&stderr, "  ");
        continue;
      }
      ascii = data[index];
      stream_print(&stderr, "%c ", isprint(ascii) ? ascii : '_');
    }
    stream_print(&stderr, "|\n");
  }
}
