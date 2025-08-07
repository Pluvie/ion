static inline void json_decode_pointer (
    void* obj,
    struct io* io,
    struct reflection* rfx,
    struct memory* allocator
)
{
  struct reflection* value_rfx = rfx->element;
  value_rfx->parent = rfx;

  void* pointer_data = memory_alloc_zero(allocator, value_rfx->size);
  json_decode(pointer_data, io, value_rfx, allocator);
  if (error.occurred)
    return;

  reflection_validate(rfx, obj);
  if (error.occurred)
    return reflection_error_extract(rfx);

  int pointer_address = (int) pointer_data;
  memcpy(obj, &pointer_address, sizeof(int));
}
