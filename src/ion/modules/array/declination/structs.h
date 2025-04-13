/**
 * The `array` type is a linear, dynamic and contiguous collection of elements of the
 * same type.
 *
 * The array uses the `memory` type to handle memory allocation. It is mandatory to
 * provide an allocator when initializing the array:
 *
 * ```c
 * memory allocator = memory_init(0);
 * array(i64) numbers = array_init(i64)(0, &allocator);
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
 * contiguous. */
typedef struct {
  u64 capacity;
  u64 length;
  t* elements;
  memory* allocator;
} array(t);
check_sizeof(array(t), 32);

typedef struct {
  t* element;
  u64 index;
} array_iterator(t);
check_sizeof(array_iterator(t), 16);
