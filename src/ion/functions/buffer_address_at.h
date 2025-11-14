void* buffer_address_at (
    struct buffer* buffer,
    uint position
);
/*
#### Description

This function returns the address of the given *buffer* space at the given *position*.
The *position* value is assumed to be in bytes. The returned address **is not**
guaranteed to be always valid: it should be discarded as soon as a call to
[buffer_push](#buffer-push) is made.

This is consistent with the linear memory management approach, where memory is
guaranteed to be contiguous, but intermediate addresses returned by each [buffer_push](
#buffer-push) call might lose validity due to the internal reallocations.

#### Return Value

A pointer to the available space in the buffer memory after an amount of bytes equal
to *position*.

#### Errors

This function never fails. If the *position* is greater than the buffer current
position, this function shall [abort](
https://www.man7.org/linux/man-pages/man3/abort.3.html).
*/
