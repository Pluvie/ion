set(t) set_init(t) (
    u64 initial_capacity,
    memory* allocator
);

set(t)* set_allocate(t) (
    u64 initial_capacity,
    memory* allocator
);

t* set_add(t) (
    set(t)* m,
    t* element
);

bool set_has(t) (
    set(t)* m,
    t* element
);

t* set_del(t) (
    set(t)* m,
    t* element
);

void set_rehash(t) (
    set(t)* m
);

static inline bool set_comparer(t) (
    t* e1,
    t* e2
);

static inline u64 set_hasher(t) (
    t* element
);
