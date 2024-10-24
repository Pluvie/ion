#ifdef ION_INCLUDED
static inline
#endif

void* tensor_at (
    struct tensor* tensor,
    struct vector* positions
)
{
  u64 position_offset = 0;
  for vector_each_with_index(
      tensor->dimensions, dimension_index, struct tensor_dimension*, dimension) {

    u64 position = as(u64, vector_get(positions, dimension_index));
    u64 dimension_offset_multiplicator = dimension->offset;
    if (dimension_offset_multiplicator == 0)
      dimension_offset_multiplicator= 1;

    position_offset += position * dimension_offset_multiplicator;
  }

  return tensor->data + (position_offset * tensor->typesize);
}
