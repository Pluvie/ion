#ifdef ION_INCLUDED
static inline
#endif

void range_set (
    struct range* range,
    i64 min,
    i64 max
)
{
  range->min = min;
  range->max = max;
  range->at = min;
}
