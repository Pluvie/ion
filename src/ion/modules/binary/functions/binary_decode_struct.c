static inline void binary_decode_struct (
    struct io* io,
    struct reflection* rfx
)
{
  for vector_each(rfx->fields, struct reflection*, field_rfx) {
    field_rfx->target = rfx->target + field_rfx->offset;
    binary_decode(io, field_rfx);
    if (error.occurred)
      return;
  }

  reflection_validate(rfx, rfx->target);
  if (error.occurred)
    return error_add_reflection_path(rfx);
}
