static inline void binary_encode_struct (
    struct reflection* rfx,
    struct io* io
)
{
  for vector_each(rfx->fields, struct reflection*, field_rfx) {
    field_rfx->target = rfx->target + field_rfx->offset;
    binary_encode(field_rfx, io);
    if (error.occurred)
      return;
  }
}
