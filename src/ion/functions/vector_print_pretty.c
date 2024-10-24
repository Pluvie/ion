#ifdef ION_INCLUDED
static inline
#endif

void vector_print_pretty (
    struct vector* vec,
    void (*printer)(void*, u64)
)
{
  void* element = NULL;

  for (u64 index = 0; index < vec->length; index++) {
    fprintf(stderr, "-----------\n");
    fprintf(stderr, "%9li |\n", index);
    fprintf(stderr, "-----------\n");

    element = vector_get(vec, index);
    if (element == NULL) {
      fprintf(stderr, "         --\n");
      continue;
    }

    printer(element, vec->typesize);
  }
}
