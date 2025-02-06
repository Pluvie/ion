struct buffer;
/**
 * The `struct buffer` is a memory abstraction, much like the `struct memory`, to
 * simplify allocation and deallocation of many objects.
 *
 * The memory shall automatically grow to fit as many objects as necessary. This struct
 * exposes the following functions to allocate memory:
 *
 * - `buffer_alloc` : allocates the given amount of memory in the allocator and returns
 *     the numerical position of this memory in the buffer.
 * - `buffer_alloc_zero` : allocates the given amount of memory in the allocator, sets
 *     its content to `0`, and returns the numerical position of this memory in the
 *     buffer.
 *
 * Memory relase is done all at once, by calling the `buffer_release` function.
 *
 * The `struct buffer` differs from the `struct memory` because memory allocation is
 * linear and never fragmented. However, its main benefit is that it does not return
 * pointers after allocations because they are not guaranteed to be always valid.
 *
 * Instead, to retrieve the pointer to an allocated memory, the function `buffer_data`
 * must be used, which accepts a buffer numerical position and returns the valid
 * pointer to its memory. */
struct buffer {
  u64 capacity;
  u64 position;
  byte* data;
  padding(8);
};
check_sizeof(struct buffer, 32);
