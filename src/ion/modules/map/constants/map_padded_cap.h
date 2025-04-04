#if defined(__AVX512F__)
  #define MAP_PADDED_CAP    16  /* How many `u32` fit into a 512-bit vector register. */

#elif defined(__AVX2__)
  #define MAP_PADDED_CAP    8   /* How many `u32` fit into a 256-bit vector register. */

#else
  #define MAP_PADDED_CAP    0   /* Not using any vector register. */

#endif
