void arena_destroy (
    struct arena* allocator
);
/*
#### Description

This function shall release to the operating system all the memory allocated by the
given `struct arena`*allocator*, and shall zero out the entire struct. All pointers
that were returned by calls to the [arena_push](#arena-push) function on this allocator
shall be invalidated.

This function should be called when the lifetime of all pointers allocated on the arena
is ended, and the memory is not needed anymore.

#### Return Value

None.

#### Errors

This function never fails.
*/
