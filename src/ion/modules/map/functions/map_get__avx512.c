{
  /* TODO

  Implementation idea:

  u32* hash = map->hashes + probe_index;

  __m512i wanted = _mm512_set1_epi64(key_hash);
  __m512i found = _mm512_load_si512(hash);
  __mmask8 cmp = _mm512_cmpeq_epi64_mask(wanted, found);

  i32 cnt = _popcnt32(cmp);

  */
}
