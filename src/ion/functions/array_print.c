void array_print (
    struct array* ary
)
{
  byte* element = NULL;

  for (u64 index = 0; index < ary->length; index++) {
    fprintf(stderr, "-----------\n");
    fprintf(stderr, "%9li |\n", index);
    fprintf(stderr, "-----------\n");

    element = (byte*) array_get(ary, index);
    if (element == NULL) {
      fprintf(stderr, "         --\n");
      continue;
    }

    hexdump(element, ary->typesize);
  }
}
