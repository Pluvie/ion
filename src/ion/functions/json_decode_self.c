static inline void json_decode_self (
    void* obj,
    struct io* io,
    struct reflection* rfx,
    struct memory* allocator
)
{
  struct reflection* self_rfx = rfx->parent;

  void* pointer_data = memory_alloc_zero(allocator, self_rfx->size);
  json_decode(pointer_data, io, self_rfx, allocator);
  if (error.occurred)
    return;

  reflection_validate(rfx, obj);
  if (error.occurred)
    return reflection_error_extract(rfx);

  int pointer_address = (int) pointer_data;
  memcpy(obj, &pointer_address, sizeof(int));
}
