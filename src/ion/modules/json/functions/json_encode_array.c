static inline void json_encode_array (
    void* obj,
    struct io* io,
    struct reflection* rfx
)
{
  io_write(io, "[", 1);
  if (error.occurred)
    return;

  struct array* array = obj;
  struct reflection* element_rfx = rfx->element;
  element_rfx->parent = rfx;

  for array_each(array, void*, element_obj, element_index) {
    element_rfx->index = element_index;

    if (element_index > 0) {
      io_write(io, ",", 1);
      if (error.occurred)
        return;
    }

    json_encode(element_obj, io, element_rfx);
    if (error.occurred)
      return;
  }

  io_write(io, "]", 1);
  if (error.occurred)
    return;
}
