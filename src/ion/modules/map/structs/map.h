struct map;
/**
 * Explain the hash map. */
struct map {
  u32 capacity;
  u32 length;
  u32 load_limit;
  u32 key_typesize;
  u32 value_typesize;
  u32 entry_typesize;
  u32* hashes;
  void* entries;
  struct memory* allocator;
  padding(16);
};
check_sizeof(struct map, 64);
