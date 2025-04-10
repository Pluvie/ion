#define decline_map_hasher_default(kt, vt)                                          _L_ \
                                                                                    _L_ \
static inline u64 map_hasher(kt, vt) (                                              _L_ \
    kt* key                                                                         _L_ \
)                                                                                   _L_ \
{                                                                                   _L_ \
  u64 hash = 5381;                                                                  _L_ \
                                                                                    _L_ \
  for (u64 i = 0; i < sizeof(kt); i++)                                              _L_ \
    hash = ((hash << 5) + hash) + ((u8*) key)[i];                                   _L_ \
                                                                                    _L_ \
  return hash;                                                                      _L_ \
}
