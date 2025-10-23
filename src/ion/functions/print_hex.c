void print_hex (
    const void* pointer,
    unsigned int length
)
{
  const char* ascii = pointer;
  const unsigned char* bytes = pointer;
  unsigned int line_length = 8;
  unsigned int groups = length / line_length;

  if (length % line_length > 0)
    groups++;

  for (unsigned int group = 0; group < groups; group++) {
    print("| ");
    for (unsigned int index = group * line_length;
        index < (group * line_length) + line_length;
        index++) {
      if (index >= length) {
        print("   ");
        continue;
      }
      print(f(bytes[index]), " ");
    }
    print("| ");
    for (unsigned int index = group * line_length;
        index < (group * line_length) + line_length;
        index++) {
      if (index >= length) {
        print("  ");
        continue;
      }
      if (ascii[index] <= 31)
        print("_ ");
      else
        print(f(ascii[index]), " ");
    }
    print("|\n");
  }
}
