static inline void json_decode_vector (
    struct io* io,
    struct reflection* rfx
)
{
  if (rfx == NULL)
    return json_decode_array(io, rfx);

decode_as_array:
  struct reflection* element_rfx = rfx->element;
  struct array array = array_init(element_rfx->size, 0, rfx->allocator);

  struct reflection array_rfx;
  memcpy(&array_rfx, rfx, sizeof(struct reflection));
  array_rfx.type = ARRAY;
  array_rfx.size_limits.min = 0;
  array_rfx.size_limits.max = 0;
  array_rfx.target = &array;

  json_decode_array(io, &array_rfx);
  if (error.occurred)
    return;

convert_to_vector:
  struct vector vector = vector_from_array(&array);

check_length:
  u64 vector_minlength = rfx->size_limits.min;
  u64 vector_maxlength = rfx->size_limits.max;

  if (vector_minlength > 0 && vector.length < vector_minlength) {
    fail("vector required minimum length of %li", vector_minlength);
    error_add_io_extraction(io);
    return error_add_reflection_path(rfx);
  }

  if (vector_maxlength > 0 && vector.length >= vector_maxlength) {
    fail("vector required maximum length of %li", vector_maxlength);
    error_add_io_extraction(io);
    return error_add_reflection_path(rfx);
  }

terminate:
  reflection_validate(rfx, &vector);
  if (error.occurred)
    return error_add_reflection_path(rfx);

  memcpy(rfx->target, &vector, sizeof(struct vector));
}
