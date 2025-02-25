struct map;
/**
 * Explain the hash map. */
struct map {
  u64 capacity;
  u64 length;
  u64 key_typesize;
  u64 value_typesize;
  u64 entry_typesize;
  void* entries;
  struct memory* allocator;
  padding(8);
};
check_sizeof(struct map, 64);
