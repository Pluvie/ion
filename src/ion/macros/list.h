/*
  This file contains all list related macros.
  
  In order to be able to use these macros, you need to define a list container type
  first. Example:
  
  ```c
  #define list_of int
  #include <ion/types/list.h>
  // Now `list<int>` type is available for use in the code.
  
  // To create a list<int> literal.
  list<int> list1 = list(int, { 3, 4, 5 });
  
  // To create a list<int> on the stack. It may only grow only up to its capacity.
  list<int> list2 = list_init(int, 256);
  
  // To create an allocated list<int>. It may grow indefinitely.
  list<int>* list3 = list_alloc(int, 0, allocator);
  ```
  
  Also, in order to simplify all list function invocations, you may implement the
  `list_function` macro which is called by all list functions. The `list_function` macro
  must be implemented on all list types that you have defined, otherwise your code will
  not compile. Here is an example implementation:
  
  ```c
  #define list_of int
  #include <ion/types/list.h>
  
  #define list_of string
  #include <ion/types/list.h>
  
  #define list_function(l, f, ...)       \
    _Generic(*(l),                       \
      list<int> : list<int>_ ## f,       \
      list<string> : list<string>_ ## f  \
    )
  ```
  
  In this way you can call whatever list function without specifying the full
  function inflected name:
  
  ```c
  list_push(string_list, s("abc"));
  // The real function call would have been:
  // `list<string>_push(string_list, s("abc"))`.
  
  list_push(int_list, 123);
  // The real function call would have been:
  // `list<int>_push(int_list, 123)`.
  ```
  
  The `list_function` macro shall automatically select the correct function based
  on the type of the list argument. This feature is available only if compiling for
  C11 standard or higher.
*/

/*
 Create a list literal. A list literal is *frozen*: it cannot be modified because it
 has fixed length and capacity, and no allocator.
*/
#define list(T, ...) {                          \
    .data = (T []) __VA_ARGS__ ,                \
    .length = countof((T []) __VA_ARGS__ ),     \
    .capacity = countof((T []) __VA_ARGS__ ),   \
  }

/**
 * Initialize a stack allocated list. This list can be modified but may grow only up
 * to its defined capacity. */
#define list_init(T, c) \
  list<T>_init(c, (T [c]) { 0 })

/**
 * Allocate a list. This list can be modified an may grow indefinitely. */
#define list_alloc(T, c, a, ...) \
  list<T>_alloc(c, a, __VA_OPT__(__VA_ARGS__ +) 0)

/**
 * Append an element to the end of list. */
#define list_push(l, e) \
  list_function(l, push)(l, e)

/**
 * Remove an element from the end of the list. */
#define list_pop(l) \
  list_function(l, pop)(l)

/**
 * Return an element at a specific position in the list. */
#define list_at(l, p) \
  list_function(l, at)(l, p)

/**
 * Loops over the elements of the list, with optional index name. */
#define list_each(l, e, ...)                                                            \
  (struct iterator iter = { 0 };                                                        \
    list_function(l, each)(l, &iter);                                                   \
    iter.position++, iter.index++)                                                      \
  for (e = (l)->data + iter.position;   iter.gate & (1<<0); iter.gate &= ~(1<<0))       \
  __VA_OPT__(                                                                           \
    for (int __VA_ARGS__ = iter.index;  iter.gate & (1<<1); iter.gate &= ~(1<<1))       \
  )
