void* allocator_pop (
    struct allocator* allocator,
    uint amount
);
/*
This function releases a given *amount* of memory from the given *allocator*.

The primary usage of a `struct allocator` is to allocate memory in chunks -- using
[allocator_push](#allocator-push) and then massively release it in one shot using
[allocator_release](#allocator-release). This is consistent with the arena memory
management principle.

However there may be some cases where some memory is not needed anymore and can be
safely released from the allocator. This function does exactly this. Note that
memory is not actually given back to the operating system, but only made available
inside the allocator.

#### Return Value

A pointer to the first available address in the *allocator* memory, after having made
enough space for it. If the *amount* is greater than the *allocator* memory, then all of
it shall be discarded and it shall be returned the beginning address of the allocator
memory.

#### Errors

This function never fails.
*/
