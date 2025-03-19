static inline void binary_encode_primitive (
    void* obj,
    struct io* io,
    struct reflection* rfx
)
{
  io_write(io, obj, rfx->size);
  if (error.occurred)
    return error_add_reflection_path(rfx);
}
