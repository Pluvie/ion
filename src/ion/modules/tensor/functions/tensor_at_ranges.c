#ifdef ION_INCLUDED
static inline
#endif

void* tensor_at_ranges (
    struct tensor* tensor,
    struct vector* ranges
)
{
  u64 position_offset = 0;
  for vector_each(
      tensor->dimensions, struct tensor_dimension*, dimension, dimension_index) {

    struct range* range = vector_get(ranges, dimension_index);

    u64 dimension_offset_multiplicator = dimension->offset;
    if (dimension_offset_multiplicator == 0)
      dimension_offset_multiplicator= 1;

    position_offset += range->at * dimension_offset_multiplicator;
  }

  return tensor->data + (position_offset * tensor->typesize);
}
