{
linear_probing:
  u32* hash = map->hashes + probe_index;

  __m256i key_hash_vec = _mm256_set1_epi32(key_hash | (u32) 0x80000000);
  __m256i hash_vec = _mm256_loadu_si256((void*) hash);
  __m256i empty_vec = _mm256_setzero_si256();

  __m256i cmp_key = _mm256_cmpeq_epi32(key_hash_vec, hash_vec);
  __m256i cmp_empty = _mm256_cmpeq_epi32(empty_vec, hash_vec);

  u32 matches = _mm256_movemask_epi8(cmp_key);
  u32 empties = _mm256_movemask_epi8(cmp_empty);

verify_matches:
  if (matches > 0)
    goto compare_key;

  if (empties > 0)
    return NULL;
  else
    goto advance_probe;

compare_key:
  u32 position = __builtin_ctz(matches) >> 2;
  void* entry = map->entries + ((probe_index + position) * map->entry_typesize);
  if (memeq(key, map_entry_key(map, entry), map->key_typesize))
    return map_entry_value(map, entry);

  matches &= (0xFFFFFFFF << (position + 4));
  goto verify_matches;

advance_probe:
  probe_index += MAP_PADDED_CAP;

  if (probe_index >= probe_index_limit) {
    probe_index = 0;
    hash = map->hashes;
    entry = map->entries;
  }

  goto linear_probing;
}
