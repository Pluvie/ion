#define   key_type(...) __key_type(__VA_ARGS__)
#define   value_type(...) __value_type(__VA_ARGS__)
#define   __key_type(k, ...) k
#define   __value_type(k, v, ...) v
#define   kt  key_type(map_declination)
#define   vt  value_type(map_declination)




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
} map_(iterator, kt, vt);
check_sizeof(map_(iterator, kt, vt), 32);




map(kt, vt) map_(init, kt, vt) (
    u64 initial_capacity,
    memory* allocator
);

vt* map_(get, kt, vt) (
    map(kt, vt)* m,
    kt* key
);

vt* map_(set, kt, vt) (
    map(kt, vt)* m,
    kt* key,
    vt* value
);

vt* map_(del, kt, vt) (
    map(kt, vt)* m,
    kt* key
);

void map_(rehash, kt, vt) (
    map(kt, vt)* m
);

static inline bool map_(comparer, kt, vt) (
    kt* k1,
    kt* k2
);

static inline u64 map_(hasher, kt, vt) (
    kt* key
);




map(kt, vt) map_(init, kt, vt) (
    u64 initial_capacity,
    memory* allocator
)
{
  u64 capacity = next_pow2(initial_capacity);
  if (capacity < MAP_CAPACITY_DEFAULT)
    capacity = MAP_CAPACITY_DEFAULT;

  u64 padded_capacity = capacity + MAP_CAPACITY_PADDING;

  map(kt, vt) m = {
    .capacity = capacity,
    .length = 0,
    .hashes = memory_alloc_zero(allocator, padded_capacity * sizeof(u64)),
    .keys = memory_alloc_zero(allocator, padded_capacity * sizeof(kt)),
    .values = memory_alloc_zero(allocator, padded_capacity * sizeof(vt)),
    .load_limit = map_load_limit(capacity),
    .allocator = allocator,
  };
  return m;
}

vt* map_(get, kt, vt) (
    map(kt, vt)* m,
    kt* key
)
{
  u64 key_hash = map_(hasher, kt, vt)(key);
  u64 probe_index = key_hash & (m->capacity - 1);
  u64 probe_index_limit = m->capacity + MAP_CAPACITY_PADDING - 1;

linear_probing:
  if (map_(comparer, kt, vt)(key, map_key_at(m, probe_index)))
    return map_value_at(m, probe_index);

  if (map_entry_is_empty(m, probe_index))
    return NULL;

  probe_index++;
  if (probe_index >= probe_index_limit)
    probe_index = 0;

  goto linear_probing;
}

vt* map_(set, kt, vt) (
    map(kt, vt)* m,
    kt* key,
    vt* value
)
{
  u64 key_hash = map_(hasher, kt, vt)(key);
  u64 probe_index = key_hash & (m->capacity - 1);
  u64 probe_index_limit = m->capacity + MAP_CAPACITY_PADDING - 1;

linear_probing:
  kt* probed_key = map_key_at(m, probe_index);
  if (map_entry_is_empty(m, probe_index))
    goto set_value_new;

  if (map_(comparer, kt, vt)(key, probed_key))
    goto set_value_existing;

  probe_index++;
  if (probe_index >= probe_index_limit)
    probe_index = 0;

  goto linear_probing;

set_value_new:
  *probed_key = *key;
  map_entry_occupy(m, probe_index, key_hash);
  m->length++;

set_value_existing:
  *map_value_at(m, probe_index) = *value;

  if (m->length >= m->load_limit)
    map_(rehash, kt, vt)(m);

  return value;
}

vt* map_(del, kt, vt) (
    map(kt, vt)* m,
    kt* key
)
{
  u64 key_hash = map_(hasher, kt, vt)(key);
  u64 probe_index = key_hash & (m->capacity - 1);
  u64 probe_index_limit = m->capacity + MAP_CAPACITY_PADDING - 1;

linear_probing:
  if (map_(comparer, kt, vt)(key, map_key_at(m, probe_index))) {
    map_entry_free(m, probe_index);
    m->length--;
    return map_value_at(m, probe_index);
  }

  if (map_entry_is_empty(m, probe_index))
    return NULL;

  probe_index++;
  if (probe_index >= probe_index_limit)
    probe_index = 0;

  goto linear_probing;
}

void map_(rehash, kt, vt) (
    map(kt, vt)* m
)
{
  u64 new_capacity = m->capacity * 2;
  map(kt, vt) rehashed_map = map_(init, kt, vt)(new_capacity, m->allocator);

  for (u64 i = 0; i < m->capacity + MAP_CAPACITY_PADDING; i++) {
    if (map_entry_is_empty(m, i))
      continue;

    kt* key = map_key_at(m, i);
    vt* value = map_value_at(m, i);
    map_(set, kt, vt)(&rehashed_map, key, value);
  }

  m->capacity = new_capacity;
  m->hashes = rehashed_map.hashes;
  m->keys = rehashed_map.keys;
  m->values = rehashed_map.values;
  m->load_limit = map_load_limit(new_capacity);
}


#ifndef map_use_comparer
#define map_use_comparer

static inline bool map_(comparer, kt, vt) (
    kt* k1,
    kt* k2
)
{
  return memeq(k1, k2, sizeof(kt));
}

#endif
#undef map_use_comparer

#ifndef map_use_hasher
#define map_use_hasher

static inline u64 map_(hasher, kt, vt) (
    kt* key
)
{
  u64 hash = 5381;

  for (u64 i = 0; i < sizeof(kt); i++)
    hash = ((hash << 5) + hash) + ((u8*) key)[i];

  return hash;
}

#endif
#undef map_use_hasher

#undef key_type
#undef value_type
#undef __key_type
#undef __value_type
#undef kt
#undef vt

/* Defined outside right before this inclusion. */
#undef map_declination
