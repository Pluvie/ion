#ifdef ION_INCLUDED
static inline
#endif

void csv_decode (
    struct io* source,
    struct object* target,
    struct csv_properties csv
)
{
//  reflect_initialize(target->reflection);
//
//check_compatibility:
//  if (!csv_is_reflection_compatible(target->reflection))
//    return;
//
//  struct reflect* element_reflection = vector_get(target->reflection->child, 0);
//  struct vector* fields = element_reflection->child;
//
//decode_headers:
//  struct map* headers = csv_decode_headers(source, fields, target->allocator, csv);
//  if (error.occurred)
//    return;
//
//  if (headers->length == 0) {
//    fail("unable to decode csv: no match found between headers and reflection fields");
//    return;
//  }
//
//decode_rows:
//  u64 element_typesize = reflect_typesize(element_reflection);
//  void* empty_element = memory_alloc_zero(target->allocator, element_typesize);
//
//  struct array rows = array_init(element_reflection, 0, target->allocator);
//
//next_row:
//  struct object row = {
//    .reflection = element_reflection,
//    .address = empty_element,
//    .allocator = target->allocator,
//  };
//
//  csv_decode_row(source, &row, headers, csv);
//  if (error.occurred)
//    return;
//
//  array_push(&rows, row->address);
//  memzero(empty_element, element_typesize);
//
//  if (io_exhausted(source))
//    goto terminate;
//
//  goto next_row;
//
//terminate:
//  memcpy(target->address, &array, sizeof(struct array));
}
