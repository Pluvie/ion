static inline void binary_decode_sequence (
    void* obj,
    struct io* io,
    struct reflection* rfx,
    struct memory* allocator
)
{
  struct reflection* element_rfx = rfx->element;
  element_rfx->parent = rfx;

  u64 sequence_length = rfx->size / element_rfx->size;

  for (u64 element_index = 0; element_index < sequence_length; element_index++) {
    element_rfx->index = element_index;
    void* element_obj = obj + (element_index * element_rfx->size);
    binary_decode(element_obj, io, element_rfx, allocator);
    if (error.occurred)
      return;
  }

  reflection_validate(rfx, obj);
  if (error.occurred)
    return error_add_reflection_path(rfx);
}
