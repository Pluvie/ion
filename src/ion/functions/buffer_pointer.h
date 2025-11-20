void* buffer_pointer (
    struct buffer* allocator
);
/*
#### Description

This function returns the address of the first available space in the given
`struct buffer` *allocator*.

This pointer **is not** guaranteed to be always valid: it should be discarded as soon
as another call to [buffer_push](#buffer-push) is made.

This is due to the design of the linear memory management, where memory is guaranteed to
be contiguous, but intermediate addresses returned by each [buffer_push](#buffer-push)
call might lose validity due to the internal reallocations.

#### Return Value

A pointer to the first available space in the buffer memory.

#### Errors

This function never fails.
*/
