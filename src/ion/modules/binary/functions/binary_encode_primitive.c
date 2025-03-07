static inline void binary_encode_primitive (
    struct reflection* rfx,
    struct io* io
)
{
  io_write(io, rfx->target, rfx->size);
  if (error.occurred)
    return error_add_reflection_path(rfx);
}
