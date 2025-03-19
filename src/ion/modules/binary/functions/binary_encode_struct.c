static inline void binary_encode_struct (
    void* obj,
    struct io* io,
    struct reflection* rfx
)
{
  for vector_each(rfx->fields, struct reflection*, field_rfx) {
    field_rfx->parent = rfx;
    void* field_obj = obj + field_rfx->offset;
    binary_encode(field_obj, io, field_rfx);
    if (error.occurred)
      return;
  }
}
