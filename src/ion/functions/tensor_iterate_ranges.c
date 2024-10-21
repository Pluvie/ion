#ifdef ION_INCLUDED
static inline
#endif

void* tensor_iterate_ranges (
    struct tensor* tensor,
    struct vector* ranges,
    struct vector* current
)
{
consistency_checks:
  if (unlikely(ranges->length != tensor->dimensions->length))
    return NULL;

  if (unlikely(ranges->length != current->length))
    return NULL;

iterate_positions:
  for (i32 i = ranges->length - 1; i >= 0; i--) {
    struct tensor_range* range = vector_get(ranges, i);
    u64 position = as(u64, vector_get(current, i));

    if (position < range->max) {
      position++;
      vector_set(current, i, &position);
      return tensor_at(tensor, current);
    }

    vector_set(current, i, &(range->min));
  }

positions_exhausted:
  return NULL;
}
