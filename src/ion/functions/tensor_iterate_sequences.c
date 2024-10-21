#ifdef ION_INCLUDED
static inline
#endif

bool tensor_iterate_sequences (
    struct tensor* tensor,
    struct vector* sequences
)
{
iterate_positions:
  for (i32 i = sequences->length - 1; i >= 0; i--) {
    struct sequence* sequence = vector_get(sequences, i);
    sequence->index++;

    if (sequence->index < sequence->values->length) {
      sequence->current = as(u64, vector_get(sequence->values, sequence->index));
      return true;
    }

    sequence->index = 0;
    sequence->current = as(u64, vector_get(sequence->values, 0));
  }

positions_exhausted:
  return false;
}
