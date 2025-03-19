#ifdef ION_INCLUDED
static inline
#endif

void csv_decode (
    void* obj,
    struct io* io,
    struct reflection* rfx,
    struct memory* allocator
)
{
check_compatibility:
  if (!csv_is_reflection_compatible(rfx))
    return;

  struct reflection* row_rfx = rfx->element;
  struct csv_properties* csv = rfx->support_data;

  row_rfx->parent = rfx;
  row_rfx->support_data = csv;

decode_headers:
  csv_decode_headers(io, row_rfx, allocator);
  if (error.occurred)
    return;

decode_rows:
  void* empty_row = memory_alloc_zero(allocator, row_rfx->size);
  struct array rows = array_init(row_rfx->size, 0, allocator);

next_row:
  row_rfx->index = rows.length;
  void* row_obj = empty_row;
  csv_decode_row(row_obj, io, row_rfx, allocator);
  if (error.occurred)
    return;

  array_push(&rows, row_obj);
  memzero(empty_row, row_rfx->size);

  if (io_exhausted(io))
    goto terminate;

  goto next_row;

terminate:
  memcpy(obj, &rows, sizeof(struct array));
}
