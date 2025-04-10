#define decline_map_comparer_default(kt, vt)                                        _L_ \
                                                                                    _L_ \
static inline bool map_comparer(kt, vt) (                                           _L_ \
    kt* k1,                                                                         _L_ \
    kt* k2                                                                          _L_ \
)                                                                                   _L_ \
{                                                                                   _L_ \
  return memeq(k1, k2, sizeof(kt));                                                 _L_ \
}
