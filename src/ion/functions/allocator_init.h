struct allocator allocator_init (
    uint capacity
);
/*
#### Description

This function initializes a `struct allocator` with the given *capacity*. It does not
perform any allocation, but the returned allocator is ready to allocate memory using
[allocator_push](#allocator-push).

#### Return Value

A `struct allocator` with the given *capacity*.
*/
