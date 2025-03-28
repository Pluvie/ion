static inline void binary_decode_array (
    void* obj,
    struct io* io,
    struct reflection* rfx,
    struct memory* allocator
)
{
read_length:
  u64* array_length = io_read(io, sizeof(u64));
  if (error.occurred)
    return error_add_reflection_path(rfx);

check_minlength:
  u64 array_minlength = rfx->size_limits.min;
  if (array_minlength > 0 && *array_length < array_minlength) {
    fail("array required minimum length of %li but found %li",
      array_minlength, *array_length);
    return error_add_reflection_path(rfx);
  }

check_maxlength:
  u64 array_maxlength = rfx->size_limits.max;
  if (array_maxlength > 0 && *array_length > array_maxlength) {
    fail("array required maximum length of %li but found %li",
      array_maxlength, *array_length);
    return error_add_reflection_path(rfx);
  }

allocate_array:
  struct reflection* element_rfx = rfx->element;
  element_rfx->parent = rfx;

  struct array array = array_init(element_rfx->size, *array_length, allocator);
  array.length = *array_length;

decode_array:
  for (u64 element_index = 0; element_index < array.length; element_index++) {
    element_rfx->index = element_index;
    void* element_obj = array.data + (element_index * element_rfx->size);
    binary_decode(element_obj, io, element_rfx, allocator);
    if (error.occurred)
      return;
  }

validate_array:
  reflection_validate(rfx, &array);
  if (error.occurred)
    return error_add_reflection_path(rfx);

copy_array:
  memcpy(obj, &array, sizeof(struct array));
}
