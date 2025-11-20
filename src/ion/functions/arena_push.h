void* arena_push (
    struct arena* allocator,
    uint amount
);
/*
#### Description

This function allocates a given `uint` *amount* of bytes on the given `struct arena`
*allocator*.

The *allocator* ensures to automatically grow its capacity in order to fit the required
*amount* of memory. This operation is transparent to the caller. The returned pointer
is guaranteed to be always valid across the entire life of the *allocator* -- i.e. up
until a call to [arena_destroy](#arena-destroy) is made.

#### Return Value

A pointer to the first available address in the *allocator* memory, after having made
enough space for it.

#### Errors

This function never fails.

In order to accomodate this call, the allocator may request memory to the operating
system. If the system is out of memory, or is either way unable to fulfill the
request, then this function shall [abort](
https://www.man7.org/linux/man-pages/man3/abort.3.html) the entire program.
*/
