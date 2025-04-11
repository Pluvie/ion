static inline u64 map_(hasher, kt, vt) (
    kt* key
)
{
  u64 hash = 5381;

  for (u64 i = 0; i < sizeof(kt); i++)
    hash = ((hash << 5) + hash) + ((u8*) key)[i];

  return hash;
}
