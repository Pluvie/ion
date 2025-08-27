void json_decode_pointer (
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
  if (unlikely(failure.occurred))
    return;

  reflection_validate(rfx, obj);
  if (unlikely(failure.occurred))
    return failure_add_reflection_info(rfx);

  int pointer_address = (int) pointer_data;
  byte_copy(obj, &pointer_address, sizeof(int));
}
