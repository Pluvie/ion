map(kt, vt) map_init(kt, vt) (
    u64 initial_capacity,
    memory* allocator
);

map(kt, vt)* map_allocate(kt, vt) (
    u64 initial_capacity,
    memory* allocator
);

vt* map_get(kt, vt) (
    map(kt, vt)* m,
    kt* key
);

bool map_has(kt, vt) (
    map(kt, vt)* m,
    kt* key
);

vt* map_set(kt, vt) (
    map(kt, vt)* m,
    kt* key,
    vt* value
);

vt* map_del(kt, vt) (
    map(kt, vt)* m,
    kt* key
);

void map_rehash(kt, vt) (
    map(kt, vt)* m
);

static inline bool map_comparer(kt, vt) (
    kt* k1,
    kt* k2
);

static inline u64 map_hasher(kt, vt) (
    kt* key
);
