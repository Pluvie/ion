#ifdef ION_INCLUDED
static inline
#endif

void array_print_pretty (
    struct array* ary,
    void (*printer)(void*, u64)
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

    printer(element, ary->typesize);
  }
}
