#ifdef ION_INCLUDED
static inline
#endif

void* map_get (
    struct map* map,
    void* key
)
{
  u64 hash = map_hash(key, map->key_typesize);
  u64 probe_index = hash & (map->capacity - 1);
  u64 probe_index_limit = map->capacity + 8 - 1;

linear_probing:
  u64* hashes = map->hashes + probe_index;

  __m512i hashes_expected = _mm512_set1_epi64(hash);
  __m512i hashes_found = _mm512_loadu_si512(hashes);

  /* Compares the two 512 bit vectors: one with the expected hash value and the other
   * with the hashes found in the map.
   *
   * [ hash, hash, hash, hash, hash, hash, hash, hash ]
   *                      ==
   * [ h+0 , h+1 , h+2 , h+3 , h+4 , h+5 , h+6 , h+7  ]
   *
   * Results are stored in a `__mmask8` type, which is a 8-bit integer with each bit
   * set to 1 if the vector element was equal, or 0 otherwise.
   *
   * [   0 ,   0 ,   1 ,   0 ,   0 ,   0 ,   0 ,   0  ]
   *
   * In the example above, the hash at position 3 in the `hashes` pointer was found
   * equal to the hash of the key given as argument. */
  __mmask8 cmp = _mm512_cmpeq_epi64_mask(hashes_expected, hashes_found);

  i32 cmp_mask = _popcnt32(cmp);
  if (cmp_mask == 0)
    goto advance_probe;

  probe_index += log2(cmp_mask);
  void* entry = map->entries + ((probe_index + i) * map_entry_typesize(map));
  if (memeq(key, map_entry_key(map, entry), map->key_typesize))
    return map_entry_value(map, entry);

advance_probe:
  probe_index += 8;
  if (probe_index >= probe_index_limit)
    probe_index = 0;

  goto linear_probing;
}
