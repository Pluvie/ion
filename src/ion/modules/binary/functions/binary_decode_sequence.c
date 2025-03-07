static inline void binary_decode_sequence (
    struct io* io,
    struct reflection* rfx
)
{
  struct reflection* element_rfx = rfx->element;
  u64 sequence_length = rfx->length;

  for (u64 element_index = 0; element_index < sequence_length; element_index++) {
    element_rfx->index = element_index;
    element_rfx->target = rfx->target + (element_index * element_rfx->size),
    binary_decode(io, element_rfx);
    if (error.occurred)
      return;
  }

  reflection_validate(rfx, rfx->target);
  if (error.occurred)
    return error_add_reflection_path(rfx);
}
