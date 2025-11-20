void* arena_push (
    struct arena* allocator,
    uint amount
);
/*
#### Description

This function allocates a given `uint` *amount* of bytes on the given `struct arena`
*allocator*.

Memory is requested to the operating system only if the arena did not yet perform
any allocation -- for example, it was just created with [arena_create](#arena-create) --
of if the arena has indeed performed previous allocations that have now reached its
capacity.

For other cases, the allocated memory is retrieved within the arena own pool.

#### Return Value

A pointer to the first available address in the *allocator* memory, after having made
enough space for it. This pointer is guaranteed to be safe and always valid throughout
all the life of the allocator. All pointers returned by this function shall be
invalidated by the [arena_destroy](#arena-destroy) call.

#### Errors

This function never fails.

If, in order to accomodate this request, the allocator must perform a request for more
memory to the operating system, and the system is out of memory, then this function
shall [abort](https://www.man7.org/linux/man-pages/man3/abort.3.html) the entire
program.
*/
