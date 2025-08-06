static inline void json_decode_int (
    void* obj,
    struct io* io,
    struct reflection* rfx,
    struct memory* allocator
)
{
  int number_length = 0;

  number_length = json_parse_number(io);
  if (error.occurred)
    return;

  if (number_length <= 0) {
    fail("expected a number");
    reflection_error_extract(rfx);
    io_error_extract(io);
    return;
  }

  slice number_string = io_read(io, number_length);
  if (error.occurred)
    return;

  if (rfx == NULL)
    return;

  int number = string_to_int((string) { number_string.data, number_string.length });
  if (error.occurred)
    return;

  memcpy(obj, &number, rfx->size);

  reflection_validate(rfx, obj);
  if (error.occurred)
    return reflection_error_extract(rfx);
}
