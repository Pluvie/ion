struct buffer buffer_create (
    uint capacity
);
/*
#### Description

This function creates a `struct buffer` with the given *capacity*. It does not perform
any allocation yet, but the returned buffer is ready to allocate memory using
[buffer_push](#buffer-push).

#### Return Value

A `struct buffer` with the given *capacity*.

#### Errors

This function never fails.
*/
