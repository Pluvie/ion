static inline void json_decode_bool (
    void* obj,
    struct io* io,
    struct reflection* rfx,
    struct memory* allocator
)
{
  int bool_length = 0;

  bool_length = json_parse_bool(io);
  if (error.occurred)
    return;

  bool value;
  io_read(io, bool_length);
  if (error.occurred)
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
    reflection_error_extract(rfx);
    io_error_extract(io);
    return;
  }

  if (rfx == NULL)
    return;

  memcpy(obj, &value, rfx->size);

  reflection_validate(rfx, obj);
  if (error.occurred)
    return reflection_error_extract(rfx);
}
