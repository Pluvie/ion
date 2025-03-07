#ifdef ION_INCLUDED
static inline
#endif

void csv_decode (
    struct io* io,
    struct reflection* rfx
)
{
check_compatibility:
  if (!csv_is_reflection_compatible(target->reflection))
    return;

  struct reflect* element_reflection = vector_get(target->reflection->child, 0);
  struct vector* fields = element_reflection->child;

decode_headers:
  struct map* headers = csv_decode_headers(io, fields, target->allocator, csv);
  if (error.occurred)
    return;

  if (headers->length == 0) {
    fail("unable to decode csv: no match found between headers and reflection fields");
    return;
  }

decode_rows:
  u64 element_typesize = reflect_typesize(element_reflection);
  void* empty_element = memory_alloc_zero(target->allocator, element_typesize);
  struct array rows = array_init(element_typesize, 0, target->allocator);

next_row:
  struct object row = {
    .reflection = element_reflection,
    .address = empty_element,
    .allocator = target->allocator,
  };

  csv_decode_row(io, &row, headers, csv);
  if (error.occurred)
    return;

  array_push(&rows, row.address);
  memzero(empty_element, element_typesize);

  if (io_exhausted(io))
    goto terminate;

  goto next_row;

terminate:
  memcpy(target->address, &rows, sizeof(struct array));
}
