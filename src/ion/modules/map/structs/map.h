struct map;
/**
 * Explain the hash map. */
struct map {
  u64 capacity;
  u64 length;
  u64 load_limit;
  u64 key_typesize;
  u64 value_typesize;
  void* hashes;
  void* entries;
  struct memory* allocator;
};
check_sizeof(struct map, 64);
