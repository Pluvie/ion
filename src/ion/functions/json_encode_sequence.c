static inline void json_encode_sequence (
    void* obj,
    struct io* io,
    struct reflection* rfx
)
{
  io_write(io, "[", 1);
  if (error.occurred)
    return;

  struct reflection* element_rfx = rfx->element;
  element_rfx->parent = rfx;
  u64 sequence_length = rfx->size / element_rfx->size;

  for (u64 i = 0; i < sequence_length; i++) {
    element_rfx->index = i;
    void* element_obj = obj + (i * element_rfx->size);

    if (i > 0) {
      io_write(io, ",", 1);
      if (error.occurred)
        return;
    }

    json_encode(element_obj, io, element_rfx);
    if (error.occurred)
      return;
  }

  io_write(io, "]", 1);
  if (error.occurred)
    return;
}
