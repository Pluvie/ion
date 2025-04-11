array(t)* array_(allocate, t) (
    u64 initial_capacity,
    memory* allocator
);

array(t) array_(init, t) (
    u64 initial_capacity,
    memory* allocator
);

t* array_(get, t) (
    array(t)* ary,
    u64 position
);

t* array_(last, t) (
    array(t)* ary
);

t* array_(pop, t) (
    array(t)* ary
);

t* array_(push, t) (
    array(t)* ary,
    t* element
);

t* array_(set, t) (
    array(t)* ary,
    u64 position,
    t* element
);
