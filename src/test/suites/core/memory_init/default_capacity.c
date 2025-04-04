test( memory_init, default_capacity ) {

  given("a struct memory allocator");
    struct memory allocator;

    u64 hash = 345678;
    i64 hashes[8] = { 0, 0, hash, 0, 0, 0, hash, 0 };
    print("heeey");
    __m512i hashes_expected = _mm512_set1_epi64(hash);
    __m512i hashes_found = _mm512_loadu_si512(hashes);
    __mmask8 cmp = _mm512_cmpeq_epi64_mask(hashes_expected, hashes_found);
    i32 cnt = _popcnt32(cmp);
    print("yo: %i", cmp);
    print("cnt: %i (%i)", cnt, __builtin_clz(cmp));


  when("providing a capacity inferior to the default");
    u64 capacity = 3;


  calling("memory_init()");
    allocator = memory_init(capacity);


  must("initialize the allocator with #MEMORY_DEFAULT_CAP capacity");
    verify(allocator.capacity == MEMORY_DEFAULT_CAP);


  success();
}
