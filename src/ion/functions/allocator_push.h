void* allocator_push (
    struct allocator* allocator,
    uint amount
);
/*
#### Description

This function allocates a given *amount* of bytes on the given *allocator*.

If the allocator has reached its capacity, or if the allocator did not yet perform any
allocations, then the required memory to accomodate this call is requested to the
operating system. This memory shall be then added to -- and managed by -- the allocator.

#### Return Value

A pointer to the first available address in the *allocator* memory, after having made
enough space for it. This pointer is guaranteed to be safe and always valid throughout
all the life of the allocator. All pointers returned by this function shall be
invalidated by the [allocator_release](#allocator-release) call.

#### Errors

This function never fails. If, in order to accomodate this request, the allocator must
perform a request for more memory to the operating system, and the hardware is out of
memory, then this function shall [abort](
https://www.man7.org/linux/man-pages/man3/abort.3.html).
*/
