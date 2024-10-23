#ifdef ION_INCLUDED
static inline
#endif

void* tensor_at_ranges (
    struct tensor* tensor,
    struct vector* ranges
)
{
  u64 position_offset = 0;
  for vector_each_with_index(
      tensor->dimensions, dimension_index, struct tensor_dimension*, dimension) {
    struct range* range = vector_get(ranges, dimension_index);
    position_offset += range->at * dimension->offset;
  }

  return tensor->data + (position_offset * tensor->typesize);
}
