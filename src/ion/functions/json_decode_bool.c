static inline void json_decode_bool (
    void* obj,
    struct io* io,
    struct reflection* rfx,
    struct memory* allocator
)
{
  int bool_length = 0;

  bool_length = json_parse_bool(io);
  if (unlikely(failure.occurred))
    return;

  bool value;
  io_read(io, bool_length);
  if (unlikely(failure.occurred))
    return;

  switch (bool_length) {
  case 4:
    value = true;
    break;
  case 5:
    value = false;
    break;
  default:
    fail("expected a boolean");
    failure_add_reflection_info(rfx);
    failure_add_io_info(io);
    return;
  }

  if (rfx == NULL)
    return;

  byte_copy(obj, &value, rfx->size);

  reflection_validate(rfx, obj);
  if (unlikely(failure.occurred))
    return failure_add_reflection_info(rfx);
}
