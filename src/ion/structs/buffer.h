struct buffer {
  byte* data;
  uint capacity;
  uint position;
};
/*
A `struct buffer` is a memory allocator. It is best used to when a program requires a
contiguous amount of memory, which can also be dynamically increased.

Imagine parsing a chunked HTTP response: you do not know how long the full response
will be; instead you receive it in chunks. Each chunk starts with a number that
indicates how many bytes the chunk content will be. You also want the final response
data to be contiguous in memory so that it is addressable by just a pointer and
therefore easy to pass it around to other functions which may, for example, parse it as
HTML, JSON, or something like that.

This is not a good case for the `struct arena` because of its memory fragmentation.
Even though each call to [arena_push](#arena-push) is guaranteed to return an always
valid address, it may not be adjacent to addresses returned by previous calls to the
same function.

Instead, a `struct buffer`, guarantees that every call to [buffer_push](#buffer-push)
produces contiguous addresses. However, in order to do so, it must invalidate all
previously returned addresses. Therefore, in order to keep track of memory allocated in
a `struct buffer`, one must use its position, which is guaranteed to be always valid,
using [buffer_position_get](#buffer-position-get).

A `struct buffer` is inherently **non thread-safe** due to the fact that allocating
memory is not an atomic operation. To be safely used in a multi threaded scenario,
you must use a mutex to synchronize the [buffer_push](#buffer-push) calls so that only
one thread can complete this call at once.
*/
