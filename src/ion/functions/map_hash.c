static inline u64 map_hash (
    void* key,
    u64 key_typesize
)
/**
 * This function returns a generic hash value based on [djb2 algorithm]
 * (http://www.cse.yorku.ca/~oz/hash.html). */
{
  u64 hash;

  if (key_typesize <= sizeof(u64)) {
    hash = *(u64*) key;
    goto ensure_not_reserved;
  }

  hash = 5381;
  byte* key_byte = (byte*) key;

  for (u64 i = 0; i < key_typesize; i++)
    hash = ((hash << 5) + hash) + *(key_byte + i); /* hash * 33 + key_byte */

  // AVX2 Test -- to be continued.
  //
  //__m512i hash_accumulator = _mm512_setzero_si512();
  //for (i64 i = key_typesize > sizeof(u64) ? sizeof(u64) : key_typesize; i > 0; i -= sizeof(u64)) {
  //  __m512i hash_vector = _mm512_maskload_epi64((i32*) key, hash_masks[i]);
  //  hash_accumulator = _mm512_add_epi64(hash_accumulator, hash_vector);
  //}

  //u64 hash = *(u64*) &hash_accumulator;

ensure_not_reserved:
  /* Ensures that hash is never equal to MAP_EMPTY_SPOT, as it is a reserved value
   * to indicate an empty map spot. */
  if (hash == MAP_EMPTY_SPOT)
    hash <<= 1;

  return hash;
}
