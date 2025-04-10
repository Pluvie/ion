#define decline_map_structs(kt, vt)                                                 _L_ \
                                                                                    _L_ \
typedef struct {                                                                    _L_ \
  u64 capacity;                                                                     _L_ \
  u64 length;                                                                       _L_ \
  u64* hashes;                                                                      _L_ \
  kt* keys;                                                                         _L_ \
  vt* values;                                                                       _L_ \
  u64 load_limit;                                                                   _L_ \
  memory* allocator;                                                                _L_ \
  padding(8);                                                                       _L_ \
} map(kt, vt);                                                                      _L_ \
check_sizeof(map(kt, vt), 64);                                                      _L_ \
                                                                                    _L_ \
typedef struct {                                                                    _L_ \
  kt* key;                                                                          _L_ \
  vt* value;                                                                        _L_ \
  u64 index;                                                                        _L_ \
  u64 hash;                                                                         _L_ \
} map_iterator(kt, vt);                                                             _L_ \
check_sizeof(map_iterator(kt, vt), 32);
