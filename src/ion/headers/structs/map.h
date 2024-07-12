struct map;
/**
 * Explain the hash map. */
struct map {
  u64 capacity;
  u64 length;
  u64 key_typesize;
  u64 value_typesize;
  void* keys;
  void* values;
  u64* hashes;
  struct memory* allocator;
};
check_sizeof(struct map, 64);
