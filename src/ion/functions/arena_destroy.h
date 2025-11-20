void arena_destroy (
    struct arena* allocator
);
/*
#### Description

This function shall release all the memory, allocated by *allocator*, back to the
operating system, and shall zero out the entire *allocator* struct. All pointers
that were returned by calls to the [arena_push](#arena-push) function, on this
*allocator*, must be considered invalid.

This function should be called when the lifetime of all pointers allocated on the arena
*allocator* is ended, and therefore the program does not need its memory anymore.

#### Return Value

None.

#### Errors

This function never fails.
*/
