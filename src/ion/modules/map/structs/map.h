struct map;
/**
 * Explain the hash map. */
struct map {
  u64 capacity;
  u64 length;
  u64 load_limit;
  u32 key_typesize;
  u32 value_typesize;
  //u32 entry_typesize;
  //u32 hash_typesize;
  //void* entries;
  u64* hashes;
  void* keys;
  void* values;
  struct memory* allocator;
};
check_sizeof(struct map, 64);
