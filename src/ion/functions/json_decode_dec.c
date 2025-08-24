static inline void json_decode_dec (
    void* obj,
    struct io* io,
    struct reflection* rfx,
    struct memory* allocator
)
{
  dec number_length = 0;

  number_length = json_parse_number(io);
  if (unlikely(failure.occurred))
    return;

  if (number_length <= 0) {
    fail("expected a number");
    failure_add_reflection_info(rfx);
    failure_add_io_info(io);
    return;
  }

  slice number_string = io_read(io, number_length);
  if (unlikely(failure.occurred))
    return;

  if (rfx == NULL)
    return;

  dec number = string_to_dec((string) { number_string.data, number_string.length });
  if (unlikely(failure.occurred))
    return;

  memcpy(obj, &number, rfx->size);

  reflection_validate(rfx, obj);
  if (unlikely(failure.occurred))
    return failure_add_reflection_info(rfx);
}
