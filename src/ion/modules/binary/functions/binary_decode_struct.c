static inline void binary_decode_struct (
    void* obj,
    struct io* io,
    struct reflection* rfx,
    struct memory* allocator
)
{
  for vector_each(rfx->fields, struct reflection*, field_rfx) {
    field_rfx->parent = rfx;
    void* field_obj = obj + field_rfx->offset;
    binary_decode(field_obj, io, field_rfx, allocator);
    if (error.occurred)
      return;
  }

  reflection_validate(rfx, obj);
  if (error.occurred)
    return error_add_reflection_path(rfx);
}
