void allocator_release (
    struct allocator* allocator
);
/*
#### Description

This function shall release all the memory allocated by the given *allocator*. The
memory is returned to the operating system. All pointers returned by the
[allocator_push](#allocator-push) function shall be invalidated.

#### Return Value

None.

#### Errors

This function never fails.
*/
