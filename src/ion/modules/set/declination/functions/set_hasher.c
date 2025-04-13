static inline u64 map_hasher(t) (
    t* element
)
{
  u64 hash = 5381;

  for (u64 i = 0; i < sizeof(kt); i++)
    hash = ((hash << 5) + hash) + ((u8*) element)[i];

  return hash;
}
