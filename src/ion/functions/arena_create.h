struct arena arena_create (
    uint capacity
);
/*
#### Description

This function creates a `struct arena` with the given *capacity*. It does not perform
any allocation yet, but the returned arena is ready to allocate memory using
[arena_push](#arena-push).

#### Return Value

A `struct arena` with the given *capacity*.
*/
