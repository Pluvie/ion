map(kt, vt) map_(init, kt, vt) (
    u64 initial_capacity,
    memory* allocator
);

map(kt, vt)* map_(allocate, kt, vt) (
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
