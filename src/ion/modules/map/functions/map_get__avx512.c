{
  //__m512i hashes_expected = _mm512_set1_epi64(hash);
  //__m512i hashes_found = _mm512_loadu_si512(hashes);
  //__mmask8 cmp = _mm512_cmpeq_epi64_mask(hashes_expected, hashes_found);
  //i32 cnt = _popcnt32(cmp);
  //print("yo: %i", cmp);
  //print("cnt: %i (%i)", cnt, __builtin_clz(cmp));
}
