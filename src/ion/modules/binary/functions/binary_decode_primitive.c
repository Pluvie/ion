static inline void binary_decode_primitive (
    struct io* io,
    struct reflection* rfx
)
{
  void* value = io_read(io, rfx->size);
  if (error.occurred)
    return error_add_reflection_path(rfx);

  if (rfx->type == BOOL) {
    /* Special case for booleans: any value other than 0 is forced as `true`. */
    if (*(u8*) value > 0)
      memcpy(rfx->target, &(bool) { true }, rfx->size);
    else
      memcpy(rfx->target, &(bool) { false }, rfx->size);

  } else {
    memcpy(rfx->target, value, rfx->size);
  }

  reflection_validate(rfx, rfx->target);
  if (error.occurred)
    return error_add_reflection_path(rfx);
}
