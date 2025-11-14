struct buffer buffer_init (
    uint capacity
);
/*
#### Description

This function initializes a `struct buffer`.

A `struct buffer` is a linear memory allocator. The buffer is useful when a contiguous
dynamic amount of memory is required. It can be seen as an infinite stack, where each
allocation is done with [buffer_push](#buffer-push). If the buffer requires more memory
to accomodate the call, it shall request it to the operating system. Also, in order to
maintain memory contiguity, a full reallocation of the buffer may be performed. For this
reason, pointers returned by buffer allocations **are not** guaranteed to be always
valid.

#### Return Value

A `struct buffer` with the given *capacity*. No allocation is performed, but the
returned buffer is ready to allocate memory using [buffer_push](#buffer-push).
ready to allocate.

#### Errors

This function never fails.
*/
