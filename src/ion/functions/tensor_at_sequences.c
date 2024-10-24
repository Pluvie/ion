#ifdef ION_INCLUDED
static inline
#endif

void* tensor_at_sequences (
    struct tensor* tensor,
    struct vector* sequences
)
{
  u64 position_offset = 0;
  for vector_each_with_index(
      tensor->dimensions, dimension_index, struct tensor_dimension*, dimension) {

    struct sequence* sequence = vector_get(sequences, dimension_index);

    u64 dimension_offset_multiplicator = dimension->offset;
    if (dimension_offset_multiplicator == 0)
      dimension_offset_multiplicator= 1;

    position_offset += sequence->current * dimension_offset_multiplicator;
  }

  return tensor->data + (position_offset * tensor->typesize);
}
