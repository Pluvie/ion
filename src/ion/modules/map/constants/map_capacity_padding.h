#if defined(__AVX512F__)
  /* How many `u64` hashes fit into a 512-bit vector register. */
  #define MAP_CAPACITY_PADDING    8

#elif defined(__AVX2__)
  /* How many `u64` hashes fit into a 256-bit vector register. */
  #define MAP_CAPACITY_PADDING    4

#else
  /* Not using any vector register. */
  #define MAP_CAPACITY_PADDING    0

#endif
