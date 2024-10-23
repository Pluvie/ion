#ifdef ION_INCLUDED
static inline
#endif

void range_set (
    struct range* range,
    u64 min,
    u64 max
)
{
  range->min = min;
  range->max = max;
  range->at = min;
}
