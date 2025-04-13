typedef struct {
  u64 capacity;
  u64 length;
  u64* hashes;
  kt* keys;
  vt* values;
  u64 load_limit;
  memory* allocator;
  padding(8);
} map(kt, vt);
check_sizeof(map(kt, vt), 64);

typedef struct {
  kt* key;
  vt* value;
  u64 index;
  u64 hash;
} map_iterator(kt, vt);
check_sizeof(map_iterator(kt, vt), 32);
