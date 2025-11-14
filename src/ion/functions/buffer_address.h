void* buffer_address (
    struct buffer* buffer
);
/*
#### Description

This function returns the address of the first available space in the given *buffer*.
This pointer **is not** guaranteed to be always valid: it should be discarded as soon
as a call to [buffer_push](#buffer-push) is made.

This is consistent with the linear memory management approach, where memory is
guaranteed to be contiguous, but intermediate addresses returned by each [buffer_push](
#buffer-push) call might lose validity due to the internal reallocations.

#### Return Value

A pointer to the first available space in the buffer memory.

#### Errors

This function never fails.
*/
