{
//linear_probing:
//  u64* hashes = map->hashes + probe_index;
//
//  __mm512i hashes_expected = _mm512_set1_epi64(hash);
//  __mm512i hashes_empty = _mm512_setzero_si512();
//  __mm512i hashes_found = _mm512_load_si512(hashes);
//
//  __mm512i cmp_expected = _mm512_cmpeq_epi64(hashes_expected, hashes_found);
//  __mm512i cmp_empty = _mm512_cmpeq_epi64(hashes_empty, hashes_found);
//
//  u64* hashes_cmp_expected = (u64*) &cmp_expected;
//  u64* hashes_cmp_empty = (u64*) &cmp_empty;
//
//  for (u32 i = 0; i < 8; i++) {
//    if (hashes_cmp_empty == 0)
//
//    if (hashes_cmp_expected[i] != 0)
//      continue;
//
//    void* entry = map->entries + ((probe_index + i) * map_entry_typesize(map));
//    if (memeq(key, map_entry_key(map, entry), map->key_typesize))
//      return map_entry_value(map, entry);
//  }
//
//  probe_index += 8;
//  if (probe_index >= probe_index_limit)
//    probe_index = 0;
//
//  goto linear_probing;
}
