static inline void binary_encode_array (
    struct reflection* rfx,
    struct io* io
)
{
  struct array* array = (struct array*) rfx->target;

check_minlength:
  u64 array_minlength = rfx->size_limits.min;
  if (array_minlength > 0 && array->length < array_minlength) {
    fail("array required minimum length of %li but found %li",
      array_minlength, array->length);
    return error_add_reflection_path(rfx);
  }

check_maxlength:
  u64 array_maxlength = rfx->size_limits.max;
  if (array_maxlength > 0 && array->length > array_maxlength) {
    fail("array required maximum length of %li but found %li",
      array_maxlength, array->length);
    return error_add_reflection_path(rfx);
  }

encode_length:
  io_write(io, &(array->length), sizeof(array->length));
  if (error.occurred)
    return error_add_reflection_path(rfx);

encode_array:
  struct reflection* element_rfx = rfx->element;

  for (u64 element_index = 0; element_index < array->length; element_index++) {
    element_rfx->index = element_index;
    element_rfx->target = array->data + (element_index * array->typesize);
    binary_encode(element_rfx, io);
    if (error.occurred)
      return;
  }
}
