static inline void binary_decode_vector (
    struct io* io,
    struct reflection* rfx
)
{
read_length:
  u64* vector_length = io_read(io, sizeof(u64));
  if (error.occurred)
    return error_add_reflection_path(rfx);

check_minlength:
  u64 vector_minlength = rfx->size_limits.min;
  if (vector_minlength > 0 && *vector_length < vector_minlength) {
    fail("vector required minimum length of %li but found %li",
      vector_minlength, *vector_length);
    return error_add_reflection_path(rfx);
  }

check_maxlength:
  u64 vector_maxlength = rfx->size_limits.max;
  if (vector_maxlength > 0 && *vector_length > vector_maxlength) {
    fail("vector required maximum length of %li but found %li",
      vector_maxlength, *vector_length);
    return error_add_reflection_path(rfx);
  }

allocate_vector:
  struct reflection* element_rfx = rfx->element;
  struct vector vector = vector_init(element_rfx->size, *vector_length, rfx->allocator);
  vector.length = *vector_length;

decode_vector:
  for (u64 element_index = 0; element_index < vector.length; element_index++) {
    element_rfx->index = element_index;
    element_rfx->target = vector.data + (element_index * element_rfx->size);
    binary_decode(io, element_rfx);
    if (error.occurred)
      return;
  }

validate_vector:
  reflection_validate(rfx, &vector);
  if (error.occurred)
    return error_add_reflection_path(rfx);

copy_vector:
  memcpy(rfx->target, &vector, sizeof(struct vector));
}
