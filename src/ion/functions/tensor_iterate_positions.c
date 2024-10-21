#ifdef ION_INCLUDED
static inline
#endif

bool tensor_iterate_positions (
    struct tensor* tensor,
    struct vector* positions
)
{
iterate_positions:
  for (i32 i = positions->length - 1; i >= 0; i--) {
    struct tensor_positions* positions = vector_get(positions, i);

    if (positions->index < positions->values->length) {
      positions->index++;
      positions->current = as(u64, vector_get(positions->values, positions->index));
      return true;
    }

    positions->index = 0;
    positions->current = as(u64, vector_get(positions->values, 0));
  }

positions_exhausted:
  return false;
}
