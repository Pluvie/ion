#ifdef ION_INCLUDED
static inline
#endif

bool tensor_iterate_ranges (
    struct tensor* tensor,
    struct vector* ranges
)
{
iterate_positions:
  for (i32 i = ranges->length - 1; i >= 0; i--) {
    struct range* range = vector_get(ranges, i);

    if (range->current < range->max) {
      range->current++;
      return true;
    }

    range->current = range->min;
  }

positions_exhausted:
  return false;
}