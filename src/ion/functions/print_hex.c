void print_hex (
    const void* pointer,
    uint length
)
{
  const char* ascii = pointer;
  const byte* bytes = pointer;
  uint line_length = 8;
  uint groups = length / line_length;
  uint group, index;

  if (length % line_length > 0)
    groups++;

  for (group = 0; group < groups; group++) {
    print("| ");
    for (index = group * line_length;
        index < (group * line_length) + line_length;
        index++) {
      if (index >= length) {
        print("   ");
        continue;
      }
      print("%02x ", bytes[index]);
    }
    print("| ");
    for (index = group * line_length;
        index < (group * line_length) + line_length;
        index++) {
      if (index >= length) {
        print("  ");
        continue;
      }
      if (ascii[index] <= 31)
        print("_ ");
      else
        print("%c ", ascii[index]);
    }
    print("|\n");
  }
}
