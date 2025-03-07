static inline void binary_encode_sequence (
    struct reflection* rfx,
    struct io* io
)
{
  struct reflection* element_rfx = rfx->element;
  u64 sequence_length = rfx->length;

  for (u64 element_index = 0; element_index < sequence_length; element_index++) {
    element_rfx->index = element_index;
    element_rfx->target = rfx->target + (element_index * element_rfx->size);
    binary_encode(element_rfx, io);
    if (error.occurred)
      return;
  }
}
