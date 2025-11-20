void* buffer_pointer_at (
    struct buffer* allocator,
    uint position
);
/*
#### Description

This function returns the address of the given `struct buffer` *allocator* at the
given *position*.

The *position* value is assumed to be in bytes. The returned address **is not**
guaranteed to be always valid: it should be discarded as soon as another call to
[buffer_push](#buffer-push) is made.

This is due to the design of the linear memory management, where memory is guaranteed to
be contiguous, but intermediate addresses returned by each [buffer_push](#buffer-push)
call might lose validity due to the internal reallocations.

#### Return Value

A pointer to the buffer memory with a byte offset equal to *position*.

#### Errors

This function never fails.

If the *position* is greater than the buffer current position, this function shall
[abort](https://www.man7.org/linux/man-pages/man3/abort.3.html) the program.
*/
