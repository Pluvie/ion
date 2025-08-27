static inline void json_decode_dec (
    void* obj,
    struct io* io,
    struct reflection* rfx,
    struct memory* allocator
)
{
  int result = json_parse_number(io);
  if (unlikely(failure.occurred))
    return;

  if (result < 0) {
    fail("expected a number");
    failure_add_reflection_info(rfx);
    failure_add_io_info(io);
    return;
  }

  if (rfx == NULL)
    return;

  dec number = string_to_dec(io->result);
  if (unlikely(failure.occurred))
    return;

  byte_copy(obj, &number, rfx->size);
  reflection_validate(rfx, obj);
  if (unlikely(failure.occurred))
    return failure_add_reflection_info(rfx);
}
