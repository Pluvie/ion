static inline void binary_decode_primitive (
    void* obj,
    struct io* io,
    struct reflection* rfx,
    struct memory* allocator
)
{
  void* value = io_read(io, rfx->size);
  if (error.occurred)
    return error_add_reflection_path(rfx);

  if (rfx->type == BOOL) {
    /* Special case for booleans: any value other than 0 is forced as `true`. */
    if (*(u8*) value > 0)
      memcpy(obj, &(bool) { true }, rfx->size);
    else
      memcpy(obj, &(bool) { false }, rfx->size);

  } else {
    memcpy(obj, value, rfx->size);
  }

  reflection_validate(rfx, obj);
  if (error.occurred)
    return error_add_reflection_path(rfx);
}
