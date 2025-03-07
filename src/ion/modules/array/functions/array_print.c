#ifdef ION_INCLUDED
static inline
#endif

void array_print (
    struct array* ary
)
{
  void* element = NULL;

  for (u64 index = 0; index < ary->length; index++) {
    fprintf(stderr, "-----------\n");
    fprintf(stderr, "%9li |\n", index);
    fprintf(stderr, "-----------\n");

    element = array_get(ary, index);
    if (element == NULL) {
      fprintf(stderr, "         --\n");
      continue;
    }

    hexdump(element, ary->typesize);
  }
}
