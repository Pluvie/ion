struct memory;
/**
 * The `struct memory` is a memory abstraction, much like the `struct buffer`, to
 * simplify allocation and deallocation of many objects.
 *
 * This struct takes inspiration from the [arena allocation](
 * https://www.rfleury.com/p/untangling-lifetimes-the-arena-allocator). It works by
 * removing the need of tracing each object own lifetime -- such when using the #malloc
 * and #free functions, and by grouping their allocation in instances of #struct memory,
 * which are oftentimes called "allocators".
 *
 * The memory shall automatically grow to fit as many objects as necessary. This struct
 * exposes the following functions to allocate memory:
 *
 * - `memory_alloc` : allocates the given amount of memory in the allocator and returns
 *     a pointer to this memory.
 * - `memory_alloc_zero` : allocates the given amount of memory in the allocator, sets
 *     its content to `0`, and returns a pointer to this memory.
 *
 * Memory relase is done all at once, by calling the `memory_release` function.
 *
 * The `struct memory` differs from the `struct buffer` because memory allocation is
 * not linear and is prone to fragmentation. However, its main benefit is that returned
 * pointers after allocations are guaranteed to be always valid. */
struct memory {
  u64 capacity;
  u64 position;
  u64 allocations;
  u64 regions_capacity;
  u64 regions_count;
  struct {
    void* address;
    u64 capacity;
  }* regions;
  byte* data;
  padding(8);
};
check_sizeof(struct memory, 64);
