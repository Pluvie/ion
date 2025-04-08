{
linear_probing:
  u64 key_hash = map_hash(key, map->key_typesize);
  u64 probe_index = key_hash & (map->capacity - 1);
  //u64 probe_index_limit = map->capacity + MAP_PADDED_CAP - 1;
  void* observed_key = map_key_at(map, probe_index);

  //switch (map->key_typesize) {
  //case sizeof(u64):
  //  return NULL;
  //  break;

  //case sizeof(u32):
    print("yooo");
    __m256i observed_keys_vec = _mm256_loadu_si256(observed_key);
    __m256i keys_vec = _mm256_set1_epi64x(as(u64, key));
    //__m256i hashes_vec = _mm256_loadu_si256((void*) map->hashes + probe_index);
    //__m256i empties_vec = _mm256_setzero_si256();

    print("obs key: %lu", *(u64*) observed_key);
    print("key: %lu", as(u64, key));
    hexdump(key, sizeof(u64));
    for (u32 i = 0; i < 4; i++) { print("observed keys vec: %u", *(((u32*)&observed_keys_vec)+i)); }
    for (u32 i = 0; i < 4; i++) { print("keys vec: %u", *(((u32*)&keys_vec)+i)); }
  //  break;

  //case sizeof(u16):
  //  return NULL;
  //  break;

  //case sizeof(u8):
  //  return NULL;
  //  break;

  //default:
  //  return NULL;
  //}

  return map_value_at(map, probe_index);

//  //__m256i key_hash_vec = _mm256_set1_epi64x(key_hash | (u64) 0x8000000000000000);
//  __m256i key_hash_vec = _mm256_setzero_si256();
//  u64* khv = (u64*) &key_hash_vec;
//  for (u32 i = 0; i < 4; i++) { print("khv: %lu", *(khv+i)); }
//  __m256i indexes_vec = _mm256_set_epi64x(
//      0*map->entry_typesize, 1*map->entry_typesize,
//      2*map->entry_typesize, 3*map->entry_typesize);
//  u64* iv = (u64*) &indexes_vec;
//  for (u32 i = 0; i < 4; i++) { print("iv: %lu", *(iv+i)); }
//  __m256i hash_vec = _mm256_i64gather_epi64(entry, indexes_vec, 1);
//  __m256i empty_vec = _mm256_setzero_si256();
//
//  __m256i cmp_key = _mm256_cmpeq_epi64(key_hash_vec, hash_vec);
//  __m256i cmp_empty = _mm256_cmpeq_epi64(empty_vec, hash_vec);
//
//  u32 matches = _mm256_movemask_epi8(cmp_key);
//  u32 empties = _mm256_movemask_epi8(cmp_empty);
//
//verify_matches:
//  if (matches > 0)
//    goto compare_key;
//
//  if (empties > 0)
//    return NULL;
//  else
//    goto advance_probe;
//
//compare_key:
//  u32 position = __builtin_ctz(matches) >> 3;
//  entry += position;
//  if (memeq(key, map_entry_key(map, entry), map->key_typesize))
//    return map_entry_value(map, entry);
//
//  matches &= (0xFFFFFFFFFFFFFFFF << (position + 8));
//  goto verify_matches;
//
//advance_probe:
//  probe_index += MAP_PADDED_CAP;
//
//  if (probe_index >= probe_index_limit) {
//    probe_index = 0;
//    entry = map->entries;
//  }
//
//  goto linear_probing;
}
