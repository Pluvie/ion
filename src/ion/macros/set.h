/*
  This file contains all set related macros.

  In order to be able to use these macros, you need to define a set container type
  first. Example:

  ```c
  #define set_of int
  #include <ion/types/set.h>
  // Now `set<int>` type is available for use in the code.

  #define set_of int
  #include <ion/types/set.c>
  // Now `set<int>` related functions are available for use in the code.

  // To create a set<int> literal.
  set<int> set1 = set(int, { 3, 4, 5 });

  // To create a set<int> on the stack. It may only grow only up to its capacity.
  set<int> set2 = set_init(int, 256);

  // To create an allocated set<int>. It may grow indefinitely.
  set<int>* set3 = set_alloc(int, 0, allocator);
  ```

  Also, in order to simplify all set function invocations, you may implement the
  `set_function` macro which is called by all set functions. The `set_function` macro
  must be implemented on all set types that you have defined, otherwise your code will
  not compile. Here is an example implementation:

  ```c
  #define set_of int
  #include <ion/types/set.h>

  #define set_of string
  #include <ion/types/set.h>

  #define set_function(type, func, ...)   \
    _Generic(type,                        \
      int     : set<int>_ ## func,        \
      string  : set<string>_ ## func      \
    )
  ```

  In this way you can call whatever set function without specifying the full
  function inflected name:

  ```c
  set_add(string_set, string("abc"));
  // The real function call would have been:
  // `set<string>_add(string_set, s("abc"))`.

  set_add(int_set, 123);
  // The real function call would have been:
  // `set<int>_add(int_set, 123)`.
  ```

  The `set_function` macro shall automatically select the correct function based
  on the type of the set argument. This feature is available only if compiling for
  C11 standard or higher.
*/

/*
  Create a set literal. A set literal is *frozen*: it cannot be modified because it
  has fixed length and capacity, and no allocator.
*/
#define set(T, ...) {                                               \
    .data = (T []) __VA_ARGS__ ,                                    \
    .length = countof((T []) __VA_ARGS__ ),                         \
    .capacity = countof((T []) __VA_ARGS__ ),                       \
    .hashes = (unsigned int [countof((T []) __VA_ARGS__ )]) { 0 }   \
  }

/*
  Initialize a stack allocated set. This set can be modified but may grow only up
  to its defined capacity.
  */
#define set_init(T, c) \
  set_function((T) { 0 }, init)(c, (T [c]) { 0 }, (unsigned int [c]) { 0 })

/*
  Allocate a set. This set can be modified an may grow indefinitely.
*/
#define set_alloc(T, c, a) \
  set_function((T) { 0 }, alloc)(c, a)

/*
  Add an element to the set.
*/
#define set_add(s, e) \
  set_function(*((s)->data), add)(s, e)

/*
  Remove an element from the set.
*/
#define set_del(s) \
  set_function(*((s)->data), del)(s)

/*
  Determine whether an element is in the set.
*/
#define set_has(s) \
  set_function(*((s)->data), has)(s)

/*
  Return an element at a specific position in the set.
*/
#define set_pos(s, p) \
  set_function(*((s)->data), pos)(s, p)

/*
  Makes space for new elements in the set.
*/
#define set_rehash(s, p) \
  set_function(*((s)->data), rehash)(s, p)

/*
  Calculates the set load limit given its capacity.
*/
#define set_load_limit(s) \
  (((s)->capacity * 70) / 100)

/*
  Check whether a set position is free or not.
*/
#define set_pos_is_free(s, p) \
  ((s)->hashes[p] == (unsigned int) 0)

/*
  Check whether a set position is occupied or not.
*/
#define set_pos_is_occupied(s, p) \
  ((s)->hashes[p] != (unsigned int) 0)

/*
  Occupies a set position.
*/
#define set_pos_occupy(s, p, h) \
  (s)->hashes[p] = ((unsigned int) h | (((unsigned int) 1)<<(INT_BIT_WIDTH-1)))

/*
  Empties a set position.
*/
#define set_pos_free(s, p) \
  (s)->hashes[p] = (unsigned int) 0

/*
  Loops over the elements of the set, with optional index name.
*/
#define set_each(s, e, ...)                                                             \
  (struct iterator iter = { 0 };                                                        \
    set_function(*((s)->data), each)(s, &iter);                                         \
    iter.position++, iter.index++)                                                      \
  for (e = (s)->data + iter.position; iter.gate & (1<<0); iter.gate &= ~(1<<0))         \
  __VA_OPT__(                                                                           \
    for (int __VA_ARGS__ = iter.index; iter.gate & (1<<1); iter.gate &= ~(1<<1))        \
  )
