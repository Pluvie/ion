#ifdef ION_INCLUDED
static inline
#endif

void vector_print (
    struct vector* vec
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

    hexdump(element, vec->typesize);
  }
}
