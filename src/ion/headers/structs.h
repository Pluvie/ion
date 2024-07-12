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




struct array;
/**
 * The #struct array is a linear, dynamic and contiguous collection of elements of the
 * same type.
 *
 * Since in C it is not possible to define type containers -- also known as type
 * generics, the array works around this limitation by using a `void*` which contains
 * the actual elements data, and a `u64` which stores the type byte size (the one
 * returned by calling #sizeof).
 *
 * The array uses a #struct memory to handle memory allocation. It is mandatory to
 * provide an allocator when initializing the array:
 *
 * ```c
 * struct memory allocator = memory_init(0);
 * struct array numbers = array_init(i64, allocator);
 * ```
 *
 * The array exposes a set of operations to work with its elements:
 *
 * - #array_push : adds an element to the array, dynamically growing its size.
 * - #array_pop : removes the last element from the array, dynamically reducing its size.
 * - #array_get : retrieves an element from the array, at a given position.
 * - #array_set : sets an element in the array, at a given position, overwriting any
 *     previous element in that position.
 *
 * It is not possible to delete elements at a given position because the array is
 * contiguous. For this kind of data structure, look no further than the #struct vector.
 */
struct array {
  u64 capacity;
  u64 length;
  u64 typesize;
  void* data;
  struct memory* allocator;
  padding(24);
};
check_sizeof(struct array, 64);




struct map;
/**
 * Explain the hash map. */
struct map {
  u64 capacity;
  u64 length;
  u64 key_typesize;
  u64 value_typesize;
  void* keys;
  void* values;
  u64* hashes;
  struct memory* allocator;
};
check_sizeof(struct map, 64);




struct io;
/**
 * Explain the io abstraction. */
struct io {
  byte* data;
  u64 length;
  u64 cursor;
  u32 flags;
  i32 descriptor;
  struct memory* allocator;
  padding(24);
};
check_sizeof(struct io, 64);




struct string;
/**
 * Explain the string (advantage of not being NULL terminated). */
struct string {
  char* content;
  u64 length;
};
check_sizeof(struct string, 16);




struct failure;
/**
 * Explain the login for normalizing all errors. */
struct failure {
  bool occurred;
  u64 length;
  char message[240];
};
check_sizeof(struct failure, 256);




struct reflect;
/**
 * Explain what reflection is and how it's useful for serialization.
 *
 * Limitations:
 *
 * - unions are not supported.
 * - structs **must** have a tag or be typedef'd: this is because the #field macro
 *   needs an identifiable struct type to calculate the field offset. Example:
 *
 * ```c
 * struct example {
 *   i32 a;
 *   struct {   // This struct won't work, because it's tagless: therefore it's not 
 *     i32 b;   // possible to calculate the offsets of its fields at compile time,
 *     i32 c;   // because the `offsetof` macro requires an identifiable tag.
 *   } d;
 * };
 * ```
 *
 * */
struct reflect {
  u64 offset;
  u64 bounds[2];
  u64 index;
  char* name;
  enum types type;
  struct reflect* parent;
  struct reflect* child;
};
check_sizeof(struct reflect, 64);




struct protocol;
/**
 * Explain what a protocol is and how it's used for serialization. */
struct protocol {
  struct reflect* schema;
  struct memory* allocator;
  struct io* input;
  struct io* output;
  struct failure* error;
  void* support_data;
  padding(16);
};
check_sizeof(struct protocol, 64);




struct sci_notation;
/**
 * Explain the scientific notation. */
struct sci_notation {
  bool negative;
  bool negative_exponent;
  struct string integer;
  struct string mantissa;
  struct string exponent;
  padding(8);
};
check_sizeof(struct sci_notation, 64);

