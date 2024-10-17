#ifdef ION_INCLUDED
static inline
#endif

void* tensor_at (
    struct tensor* tensor,
    struct vector* positions
)
{
dimensions_check:
  if (unlikely(positions->length != tensor->dimensions->length)) {
    fprintf(stderr,
      "fatal: positions not matching dimensions [%p]\n",
      tensor);

    abort();
  }

position_check:
  for vector_each_with_index(positions, index, u64*, position) {
    u64 dimension_length = as(u64, vector_get(tensor->dimensions, index));
    if (unlikely(position >= dimension_length)) {
      fprintf(stderr,
        "fatal: position %li out of dimension %li bounds [%p]\n",
        position, index, tensor);

      abort();
    }
  }

at:
  u64 position_offset = 0;
  for vector_each_with_index(positions, index, u64*, position) {
    u64 offset = as(u64, vector_get(tensor->offsets, index));
    position_offset += position * offset;
  }

  return tensor->data + (position_offset * tensor->typesize);
}
