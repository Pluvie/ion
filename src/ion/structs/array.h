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
