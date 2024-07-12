static inline u64 map_hash (
    void* key,
    u64 key_typesize
)
/**
 * This function returns a generic hash value based on [djb2 algorithm]
 * (http://www.cse.yorku.ca/~oz/hash.html). */
{
  u64 hash = 5381;
  byte key_byte = 0;
  byte* key_bytes = (byte*) key;

  for (u64 i = 0; i < key_typesize; i++) {
    key_byte = key_bytes[i];
    hash = ((hash << 5) + hash) + key_byte; /* hash * 33 + character */
  }

  return hash;
}
