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

  struct reflect* struct_rfx = rfx->element;
  struct csv* rfx->support_data;

decode_headers:
  struct array* headers = csv_decode_headers(io, struct_rfx, csv);
  if (error.occurred)
    return;

decode_rows:
  void* empty_row = memory_alloc_zero(rfx->allocator, struct_rfx->size);
  struct array rows = array_init(struct_rfx->size, 0, rfx->allocator);

next_row:
  struct_rfx->index = rows.length;
  struct_rfx->target = empty_row;
  csv_decode_row(io, struct_rfx, headers, csv);
  if (error.occurred)
    return;

  array_push(&rows, elmement_rfx->target);
  memzero(empty_row, struct_rfx->size);

  if (io_exhausted(io))
    goto terminate;

  goto next_row;

terminate:
  memcpy(rfx->target, &rows, sizeof(struct array));
}
