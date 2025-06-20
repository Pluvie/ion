/**
 * This file contains all map related macros.
 *
 * In order to be able to use these macros, you need to define a map container type
 * first. Example:
 *
 * ```c
 * #define map_of int, int
 * #include <ion/types/map.h>
 * // Now `map<int, int>` type is available for use in the code.
 *
 * // To create a map<int, int> literal.
 * map<int, int> map1 = map(int, int, { 3, 4, 5 });
 *
 * // To create a map<int, int> on the stack. It may only grow only up to its capacity.
 * map<int, int> map2 = map_init(int, int, 256);
 *
 * // To create an allocated map<int, int>. It may grow indefinitely.
 * map<int, int>* map3 = map_alloc(int, int, 0, allocator);
 * ```
 *
 * Also, in order to simplify all map function invocations, you may implement the
 * `map_function` macro which is called by all map functions. The `map_function` macro
 * must be implemented on all map types that you have defined, otherwise your code will
 * not compile. Here is an example implementation:
 *
 * ```c
 * #define map_of int
 * #include <ion/types/map.h>
 *
 * #define map_of string
 * #include <ion/types/map.h>
 *
 * #define map_function(m, f, ...)                      \
 *   _Generic(*(m),                                     \
 *     map<int, int> : map<int, int>_ ## f,             \
 *     map<string, string> : map<string, string>_ ## f  \
 *   )
 * ```
 *
 * In this way you can call whatever map function without specifying the full
 * function mangled name:
 *
 * ```c
 * map_set(string_map, s("abc"), s("xyz"));
 * // The real function call would have been:
 * // `map<string>_set(string_map, s("abc"), s("xyz"))`.
 *
 * map_set(int_map, 123, 789);
 * // The real function call would have been:
 * // `map<int>_set(int_map, 123, 789)`.
 * ```
 *
 * The `map_function` macro shall automatically select the correct function based
 * on the type of the map argument. */

/**
 * Create a map literal. A map literal is *frozen*: it cannot be modified because it
 * has fixed length and capacity, and no allocator. */
#define map(kt, vt, ...)                                              \
  map<kt, vt>_literal(                                                \
    countof((struct { kt k; vt v; } []) __VA_ARGS__ ),                \
    (kt [countof((struct { kt k; vt v; } []) __VA_ARGS__ )]) { 0 } ,  \
    (vt [countof((struct { kt k; vt v; } []) __VA_ARGS__ )]) { 0 } ,  \
    (int [countof((struct { kt k; vt v; } []) __VA_ARGS__ )]) { 0 },  \
    (struct { kt k; vt v; } []) __VA_ARGS__                           \
  )

/**
 * Initialize a stack allocated map. This map can be modified but may grow only up
 * to its defined capacity. */
#define map_init(kt, vt, c) \
  map<kt, vt>_init(c, (kt [c]) { 0 }, (vt [c]) { 0 }, (int [c]) { 0 })

/**
 * Allocate a map. This map can be modified an may grow indefinitely. */
#define map_alloc(kt, vt, c, a) \
  map<kt, vt>_alloc(c, a)

/**
 * Return the value of the given key in the map. */
#define map_get(m, k) \
  map_function(m, get)(m, k)

/**
 * Set a key / value pair in the map. */
#define map_set(m, k, v) \
  map_function(m, set)(m, k, v)

/**
 * Remove a key from the map. */
#define map_del(m, k) \
  map_function(m, del)(m, k)

/**
 * Determine whether a key is in the map. */
#define map_has(m, k) \
  map_function(m, has)(m, k)

/**
 * Loops over the keys and values of the map, with optional index name. */
#define map_each(m, k, v, ...)                                                          \
  (struct iterator iter = { 0 };                                                        \
    map_function(m, each)(m, &iter);                                                    \
    iter.position++, iter.index++)                                                      \
  for (k = (m)->keys.data + iter.position; iter.gate & (1<<0); iter.gate &= ~(1<<0))    \
  for (v = (m)->values + iter.position;    iter.gate & (1<<1); iter.gate &= ~(1<<1))    \
  __VA_OPT__(                                                                           \
    for (int __VA_ARGS__ = iter.index;     iter.gate & (1<<2); iter.gate &= ~(1<<2))    \
  )
