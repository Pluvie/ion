/**
 * This file contains all set related macros.
 *
 * In order to be able to use these macros, you need to define a set container type
 * first. Example:
 *
 * ```c
 * #define set_of int
 * #include <ion/types/set.h>
 * // Now `set<int>` type is available for use in the code.
 *
 * // To create a set<int> literal.
 * set<int> set1 = set(int, { 3, 4, 5 });
 *
 * // To create a set<int> on the stack. It may only grow only up to its capacity.
 * set<int> set2 = set_init(int, 256);
 *
 * // To create an allocated set<int>. It may grow indefinitely.
 * set<int>* set3 = set_alloc(int, 0, allocator);
 * ```
 *
 * Also, in order to simplify all set function invocations, you may implement the
 * `set_function` macro which is called by all set functions. The `set_function` macro
 * must be implemented on all set types that you have defined, otherwise your code will
 * not compile. Here is an example implementation:
 *
 * ```c
 * #define set_of int
 * #include <ion/types/set.h>
 *
 * #define set_of string
 * #include <ion/types/set.h>
 *
 * #define set_function(s, f, ...)      \
 *   _Generic(*(s),                     \
 *     set<int> : set<int>_ ## f,       \
 *     set<string> : set<string>_ ## f  \
 *   )
 * ```
 *
 * In this way you can call whatever set function without specifying the full
 * function mangled name:
 *
 * ```c
 * set_add(string_set, s("abc"));
 * // The real function call would have been:
 * // `set<string>_add(string_set, s("abc"))`.
 *
 * set_add(int_set, 123);
 * // The real function call would have been:
 * // `set<int>_add(int_set, 123)`.
 * ```
 *
 * The `set_function` macro shall automatically select the correct function based
 * on the type of the set argument. */

/**
 * Create a set literal. A set literal is *frozen*: it cannot be modified because it
 * has fixed length and capacity, and no allocator. */
#define set(t, ...)                             \
  set<t>_literal(                               \
    countof((t []) __VA_ARGS__ ),               \
    (t []) __VA_ARGS__ ,                        \
    (int [countof((t []) __VA_ARGS__ )]) { 0 }  \
  )

/**
 * Initialize a stack allocated set. This set can be modified but may grow only up
 * to its defined capacity. */
#define set_init(t, c) \
  set<t>_init(c, (t [c]) { 0 }, (int [c]) { 0 })

/**
 * Allocate a set. This set can be modified an may grow indefinitely. */
#define set_alloc(t, c, a, ...) \
  set<t>_alloc(c, a, __VA_OPT__(__VA_ARGS__ +) 0)

/**
 * Add an element to the set. */
#define set_add(s, e) \
  set_function(s, add)(s, e)

/**
 * Remove an element from the set. */
#define set_del(s, e) \
  set_function(s, del)(s, e)

/**
 * Determine whether an element is in the set. */
#define set_has(s, e) \
  set_function(s, has)(s, e)

/**
 * Return an element sequential position in the set. */
#define set_pos(s, e) \
  set_function(s, pos)(s, e)

/**
 * Makes space for new elements in the set. */
#define set_rehash(s) \
  set_function(s, rehash)(s)

/**
 * Calculates the set load limit given its capacity. */
#define set_load_limit(s) \
  (((s)->capacity * 70) / 100)

/**
 * Check whether a set position is free or not. */
#define set_pos_is_free(s, p) \
  ((s)->hashes[p] == (int) 0)

/**
 * Check whether a set position is occupied or not. */
#define set_pos_is_occupied(s, p) \
  ((s)->hashes[p] != (int) 0)

/**
 * Occupies a set position. */
#define set_pos_occupy(s, p, h) \
  (s)->hashes[p] = ((int) h | (int) 0x8000000000000000)

/**
 * Empties a set position. */
#define set_pos_free(s, p) \
  (s)->hashes[p] = (int) 0

/**
 * Loops over the elements of the set, with optional index name. */
#define set_each(s, e, ...)                                                             \
  (struct iterator iter = { 0 };                                                        \
    set_function(s, each)(s, &iter);                                                    \
    iter.position++, iter.index++)                                                      \
  for (e = (s)->data + iter.position;   iter.gate & (1<<0); iter.gate &= ~(1<<0))       \
  __VA_OPT__(                                                                           \
    for (int __VA_ARGS__ = iter.index;  iter.gate & (1<<1); iter.gate &= ~(1<<1))       \
  )
