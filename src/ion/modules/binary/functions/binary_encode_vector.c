static inline void binary_encode_vector (
    void* obj,
    struct io* io,
    struct reflection* rfx
)
{
  struct vector* vector = (struct vector*) obj;

check_minlength:
  u64 vector_minlength = rfx->size_limits.min;
  if (vector_minlength > 0 && vector->length < vector_minlength) {
    fail("vector required minimum length of %li but found %li",
      vector_minlength, vector->length);
    return error_add_reflection_path(rfx);
  }

check_maxlength:
  u64 vector_maxlength = rfx->size_limits.max;
  if (vector_maxlength > 0 && vector->length > vector_maxlength) {
    fail("vector required maximum length of %li but found %li",
      vector_maxlength, vector->length);
    return error_add_reflection_path(rfx);
  }

encode_length:
  io_write(io, &(vector->length), sizeof(vector->length));
  if (error.occurred)
    return error_add_reflection_path(rfx);

encode_vector:
  struct reflection* element_rfx = rfx->element;
  element_rfx->parent = rfx;

  for (u64 element_index = 0; element_index < vector->length; element_index++) {
    element_rfx->index = element_index;
    void* element_obj = vector->data + (element_index * vector->typesize);
    binary_encode(element_obj, io, element_rfx);
    if (error.occurred)
      return;
  }
}
