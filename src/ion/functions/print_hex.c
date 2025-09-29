void print_hex (
    const void* pointer,
    unsigned int length
)
{
  const char* data = pointer;
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
      print(f(data[index]), " ");
    }
    print("| ");
    for (unsigned int index = group * line_length;
        index < (group * line_length) + line_length;
        index++) {
      if (index >= length) {
        print("  ");
        continue;
      }
      if (data[index] <= 31)
        print("_ ");
      else
        print(f(data[index]), " ");
    }
    print("|\n");
  }
}
