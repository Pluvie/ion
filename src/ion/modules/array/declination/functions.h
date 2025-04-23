array(t)* array_allocate(t) (
    u64 initial_capacity,
    memory* allocator
);

array(t) array_init(t) (
    u64 initial_capacity,
    memory* allocator
);

t* array_get(t) (
    array(t)* array,
    u64 position
);

t* array_last(t) (
    array(t)* array
);

t* array_pop(t) (
    array(t)* array
);

t* array_push(t) (
    array(t)* array,
    t* element
);

t* array_set(t) (
    array(t)* array,
    u64 position,
    t* element
);
