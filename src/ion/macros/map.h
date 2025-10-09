/*
  This file contains all map related macros.

  In order to be able to use these macros, you need to define a map container type
  first. Example:

  ```c
  #define map_of char*, int
  #include <ion/types/map.h>
  // Now `map<char*, int>` type is available for use in the code.

  #define map_of char*, int
  #include <ion/types/map.c>
  // Now `map<char*, int>` related functions are available for use in the code.

  // To create a map<char*, int> literal.
  map<int> map1 = map(int, { { "a", 3 }, { "b", 4 }, { "c", 5 } });

  // To create a map<char*, int> on the stack. It may only grow only up to its capacity.
  map<int> map2 = map_init(char*, int, 256);

  // To create an allocated map<int>. It may grow indefinitely.
  map<int> map3 = map_alloc(char*, int, 0, allocator);
  ```

  Also, in order to simplify all map function invocations, you may implement the
  `map_function` macro which is called by all map functions. The `map_function` macro
  must be implemented on all map types that you have defined, otherwise your code will
  not compile. Here is an example implementation:

  ```c
  #define map_of char*, int
  #include <ion/types/map.h>

  #define map_of char*, dec
  #include <ion/types/map.h>

  #define map_function(key_type, value_type, func, ...)   \
    _Generic(key_type,                                    \
      char* : _Generic(value_type,                        \
        int : map<char*, int>_ ## func,                   \
        dec : map<char*, dec>_ ## func                    \
      )                                                   \
    )
  ```

  In this way you can call whatever map function without specifying the full
  function inflected name:

  ```c
  map_set(int_map, "abc", 123);
  // The real function call would have been:
  // `map<char*, int>_set(int_map, "abc", 123)`.

  map_add(dec_map, 123.456);
  // The real function call would have been:
  // `map<char*, dec>_set(dec_map, "abc", 123.456)`.
  ```

  The `map_function` macro shall automatically select the correct function based
  on the type of the map argument. This feature is available only if compiling for
  C11 standard or higher.
*/

/*
  Create a map literal. A map literal is *frozen*: it cannot be modified because it
  has fixed length and capacity, and no allocator.
*/
#define map(K, V, ...) \
  map_function((map<K, V>) { 0 }, literal)( \
    countof((struct { K k; V v; } []) __VA_ARGS__), \
    (K [countof((struct { K k; V v; } []) __VA_ARGS__)]) { 0 }, \
    (V [countof((struct { K k; V v; } []) __VA_ARGS__)]) { 0 }, \
    (unsigned int [countof((struct { K k; V v; } []) __VA_ARGS__)]) { 0 }, \
    (struct { K k; V v; } []) __VA_ARGS__)

/*
  Initialize a stack allocated map. This map can be modified but may grow only up
  to its defined capacity.
*/
#define map_init(K, V, c) \
  map_function((map<K, V>) { 0 }, init)( \
    c, (K [c]) { 0 }, (V [c]) { 0 }, (unsigned int [c]) { 0 })

/*
  Allocate a map. This map can be modified an may grow indefinitely.
*/
#define map_alloc(K, V, c, a) \
  map_function((map<K, V>) { 0 }, alloc)(c, a)

/*
  Get the value of a key in the map.
*/
#define map_get(m, k) \
  map_function(*(m), get)(m, k)

/*
  Set a key / value pair in the map.
*/
#define map_set(m, k, v) \
  map_function(*(m), set)(m, k, v)

/*
  Remove a key and its associated value from the map.
*/
#define map_del(m, k) \
  map_function(*(m), del)(m, k)

/*
  Determine whether an key is in the map.
*/
#define map_has(m, k) \
  map_function(*(m), has)(m, k)

/*
  Loops over the key / value pairs of the map, with optional index name.
*/
#define map_each(m, k, v, ...)                                                          \
  (struct iterator iter = { 0 };                                                        \
    map_function(*(m), each)(m, &iter); iter.position++, iter.index++)                  \
  for (k = (m)->keys.data + iter.position; iter.gate & (1<<0); iter.gate &= ~(1<<0))    \
  for (v = (m)->values + iter.position; iter.gate & (1<<1); iter.gate &= ~(1<<1))       \
  __VA_OPT__(                                                                           \
    for (int __VA_ARGS__ = iter.index; iter.gate & (1<<2); iter.gate &= ~(1<<2))        \
  )
