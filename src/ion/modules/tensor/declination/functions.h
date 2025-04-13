tensor(t)* tensor_allocate(t) (
    array(u64)* dimensions,
    memory* allocator
);

tensor(t) tensor_init(t) (
    array(u64)* dimensions,
    memory* allocator
);

t* tensor_at(t) (
    tensor(t)* tns,
    array(u64)* positions
);
