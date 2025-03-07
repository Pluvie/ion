#ifdef ION_INCLUDED
static inline
#endif

void csv_decode (
    struct io* io,
    struct reflection* rfx
)
{
check_compatibility:
  if (!csv_is_reflection_compatible(rfx))
    return;

  struct reflect* element_rfx = rfx->element;
  struct vector* fields = element_rfx->fields;
  struct csv* rfx->support_data;

decode_headers:
  struct map* headers = csv_decode_headers(io, fields, rfx->allocator, csv);
  if (error.occurred)
    return;

  if (headers->length == 0) {
    fail("unable to decode csv: no match found between headers and reflection fields");
    return;
  }

decode_rows:
  struct array rows = array_init(element_rfx->size, 0, rfx->allocator);
  void* empty_row = memory_alloc_zero(rfx->allocator, element_rfx->size);

next_row:
  element_rfx->index = rows.length;
  element_rfx->target = empty_row;
  csv_decode_row(io, &row, headers, csv);
  if (error.occurred)
    return;

  array_push(&rows, elmement_rfx->target);
  memzero(empty_row, element_rfx->size);

  if (io_exhausted(io))
    goto terminate;

  goto next_row;

terminate:
  memcpy(rfx->target, &rows, sizeof(struct array));
}
