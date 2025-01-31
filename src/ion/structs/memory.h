struct memory;
/**
 * The #struct memory is a memory abstraction to simplify allocation and deallocation
 * of many objects.
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
 * - #memory_alloc : allocates the given amount of memory in the allocator
 * - #memory_alloc_zero : allocates the given amount of memory in the allocator, and
 *     sets its content to `0`.
 *
 * Memory relase is done all at once, by calling the #memory_release function. */
struct memory {
  u64 capacity;
  u64 position;
  u64 allocations;
  u64 regions_capacity;
  u64 regions_count;
  struct {
    byte* address;
    u64 capacity;
  }* regions;
  byte* data;
  padding(8);
};
check_sizeof(struct memory, 64);
