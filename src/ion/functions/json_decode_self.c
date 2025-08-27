static inline void json_decode_self (
    void* obj,
    struct io* io,
    struct reflection* rfx,
    struct memory* allocator
)
{
  struct reflection* self_rfx = reflection_self_get(rfx);

  void* pointer_data = memory_alloc_zero(allocator, self_rfx->size);
  json_decode(pointer_data, io, self_rfx, allocator);
  if (unlikely(failure.occurred))
    return;

  reflection_validate(rfx, obj);
  if (unlikely(failure.occurred))
    return failure_add_reflection_info(rfx);

  int pointer_address = (int) pointer_data;
  byte_copy(obj, &pointer_address, sizeof(int));
}
