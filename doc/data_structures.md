<div align="center">
  <h1>⚡️ION⚡️</h1>
  <h3>Super C harge!</h3>
</div>

## Data Structures

```c
map<char*, int> oceans = map(char*, int, {
  { "Pacific", 179000000 },
  { "Atlantic", 120000000 },
  { "Indian", 73600000 },
});

int* pacific_sqm_size = map_get(&oceans, "Pacific");  // points to 179000000
int* arctic_sqm_size = map_get(&oceans, "Arctic");    // NULL
map_set(&oceans, "Arctic", 5400000);
arctic_sqm_size = map_get(&oceans, "Arctic");         // points to 5400000
```

Or even:

```c
struct squadmate {
  enum classes class;
  int health;
  int shields;
};

enum classes {
  SOLDIER,
  VANGUARD,
  INFILTRATOR,
  ENGINEER,
  SENTINEL,
  ADEPT,
};

struct squadmate Shepard = { SOLDIER, 500, 500 };
struct squadmate Garrus = { INFILTRATOR, 400, 600 };
struct squadmate Liara = { ADEPT, 200, 600 };
struct squadmate Tali = { ENGINEER, 300, 500 };
struct squadmate Wrex = { VANGUARD, 800, 500 };

list<struct squadmate> squad = list_init(struct squadmate, 3);

list_push(&squad, &Shepard);
list_push(&squad, &Liara);
list_push(&squad, &Wrex);

// Ready to deploy!

```

This is made possible by adding a preprocessing step that injects just after the
standard preprocessor and before the actual compilation. The step is very
straightforward: finds all occurrences of `[a-z]<...>` and replaces them with the
inflected version following these simple rules:

  1. All spaces become underscores.
  2. All occurrences of `*` become `_p`.
  3. All alphanumeric character are left unchanged.
  4. Every other special character is removed.

This generates unique names for every required data structure of a given type, and also
guarantees full type safety.

Let's take a look at some examples on how you can use these data structures:

### List

A list is a sequence of adjacent elements of the same type. It has the benefit of *O(1)*
random access complexity, but random insert or delete is *O(n)*.

```c
#define list_of char*
#include <ion/types/list.h>
// To create a list of char pointers.
```

Using the `#define list_of` prepares the list definition, followed by the type of which
the elements of the list are made of. The type can be any C type, such as
`struct mystruct`, `enum myenum`, pointers like `int*`, `char**` and even other
data structures.

Then the `#include <ion/types/list.h>` directive does all the work needed to define
the inflected list functions and structs. The available operations shall be:

```c
list<char*> ninja_turtles = list(char*,
  { "Leonardo", "Donatello", "Raffaello", "Michelangelo" });
// This is a list literal, stack allocated, frozen and unmodifiable.

list<char*> stack_list = list_init(char*, 8);
// This is a stack allocated list, modifiable but cannot grow over its capacity: `8` in this case.

list<char*>* heap_list = list_alloc(char*, 128, allocator);
// This is a heap allocated list, modifiable and can grow indefinitely.


list<char*>_push(heap_list, "January");
// Appends an element to the list. Automatically grows the necessary memory.

list<char*>_get(heap_list, 0); // returns a pointer to: "January"
// Fetches the nth element from the list, with bounds checking.

list<char*>_pop(heap_list); // returns: "January"
// Removes an element from the end of the list.
```

All list functions calls may be shortened by defining the `list_function` macro:

```c
#define list_function(v, f, ...)      \
  _Generic(*(v),                      \
    list<char*> : list<char*>_ ## f,  \
    ... other defined list types      \
  )
```

This allows to call the previous functions like this:

```c
list_push(heap_list, "January";
list_get(heap_list, 0);
list_pop(heap_list);
```

This works because ⚡️ION⚡️ internally already reroutes all `list_...` functions calls
to the `list_function` macro.

The `list_function` macro must be defined only once when all list types are known, due
to how the `_Generic` expression works.

### Set

A set is an unordered collection of elements of the same type. The elements in the set
are unique: each element can appear at most once. Sets have *O(1)* complexity in
random insertion, deletion and access, but have the drawback that elements do not
have an order and they are not stored adjacent to each other.

```c
#define set_of int
#include <ion/types/set.h>
```

Available operations are:

```c
set<int> primes = set(int, { 2, 3, 5, 7, 11 });
set<int> stack_set = set_init(int, 8);
set<int>* heap_set = set_alloc(int, 128, allocator);

set_add(heap_set, 13);
set_has(heap_set, 6); // returns false
set_del(heap_set, 2);
```

### Map

A map is a combination of a set (called keys) with a list of values. This allows to
create associations between unique keys and values. Maps have *O(1)* complexity in
random insertion, deletion and access, but have the drawback that keys and values do not
have an order and they are not stored adjacent to each other.

```c
#define map_of char*, int
#include <ion/types/map.h>
```

Available operations are:

```c
map<char*, int> oceans = map(char*, int, {
  { "Pacific", 179000000 },
  { "Atlantic", 120000000 },
  { "Indian", 73600000 },
});
map<char*, int> stack_map = map_init(int, 8);
map<char*, int>* heap_map = map_alloc(int, 128, allocator);

map_set(heap_map, "Antartic", 21960000);
map_has(heap_map, "Artic"); // returns false
map_has(heap_map, "Antartic"); // returns true
map_del(heap_map, "Antartic");
```
