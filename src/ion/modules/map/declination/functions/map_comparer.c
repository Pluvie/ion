static inline bool map_comparer(kt, vt) (
    kt* k1,
    kt* k2
)
{
  return memeq(k1, k2, sizeof(kt));
}
