<div align="center">
  <h1>⚡️ION⚡️</h1>
  <h3>Super C harge!</h3>
</div>

## Introduction

⚡️ION⚡️ is a C substratum that aims to provide many useful features through *syntax
elegance* and *semantic cohesion*.

## Features

Ion shall provide efficient language constructs to:

  - offer ready to use data structures like [lists](#list), [maps](#map) and
    [sets](#set) which can hold any type.
  - [serialize](#serialization) to / from many data formats like JSON, XML, CSV,
    etc. and provide an easy way to create your serialization in any other new format.
  - enable the introspection of any C language struct through [reflection](#reflection).
  - introduce a [memory management](#memory) approach that can revolutionize
    the way C code is written.

and many other minor improvements like:

  - normalize [io operations](#io) on files, sockets, and memory objects.
  - [standardize data types](#types): integers, decimals, strings, etc.

## Motivation

C is [old](https://dl.acm.org/doi/10.1145/155360.155580). Probably older than most of
us reading this text. It has resisted the trial of time, and still runs under the vast
majority of our machines.

And rightfully so. Its concept and design are pristine and simple. Its speed, unmatched.
⚡️ION⚡️ wants to capitalize upon this heritage, by giving tools that can can extend its
usage in the current programming landscape.

We believe that the status of the modern software ecosystem is bad. Programs are slow
and expensive. This is, in our opinion, due to two main reasons:

  1. the programming language landscape is all about abstraction and object-oriented
     approach, but this has [little to do](https://caseymuratori.com/blog_0015) with
     the real computer world and leads to..
  2. programmers not becoming aware of how the underlying hardware works and thus
     are unable to optimize for performance.

We hope to show that achieving code clarity and efficiency is not only still possible,
but it has been so since the early days. Only by choosing the wrong evolution path did
we reach this stagnation point. We need to return to our roots and build again from
there: this is why ⚡️ION⚡️ is born.

## Data Structures

A big part of computer science theory revolves around algorithms and data structures.
They have been extensively used to [solve real-world problems](
https://en.wikipedia.org/wiki/Seven_Bridges_of_K%C3%B6nigsberg) in the most efficient
way possible.

However, back in the 1970s, when C was born, computers were not as widespread as they
are now, and a lot of research had yet to be done. Over the following years, it became
more and more evident how they could rapidly solve complex computational problems by
simply implementing the correct -- and mathematically already well-defined -- algorithms
and data structures.

This is why C lags behind in this compartment compared to newer languages. It is not
the fact that it's not possible to *implement* these things in C -- it is of course
[Turing Complete](https://en.wikipedia.org/wiki/Turing_completeness) -- but rather the
fact that it does not expose a syntactical and type-safe way to do so.

We posit that all that is required to achieve this is a __symbol inflection__ directly
[integrated in the preprocessor](bin/ion.py). Using ⚡️ION⚡️, it is possible to do things
like:

```c
map<char*, int> oceans = map(char*, int, {
  { "Pacific", 179000000 },
  { "Atlantic", 120000000 },
  { "Indian", 73600000 },
});
```

Or even:

```c
eunm roulette_color {
  GREEN,
  RED,
  BLACK,
};

struct roulette_number {
  int number;
  enum roulette_color color;
};

list<struct roulette_number> roulette = list(struct roulette_number, {
  { 0, GREEN },
  { 1, RED },
  { 2, BLACK },
  ...
});
```

This is made possible by adding a preprocessing step that injects just after the
standard preprocessor and before the actual compilation. The step is very
straightforward: finds all occurrences of `[a-z]<...>` and replaces them with the
inflected version following these simple rules:

  1. All spaces become undersores.
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

### Types

⚡️ION⚡️ aims to standardize the way C code is written by setting a convention on types.
The base types that are available are:

  - `int` a 64bit signed integer.
  - `dec` a 64bit double precision decimal.
  - `bool` a 32bit boolean value.
  - `char` a 8bit signed integer representing ASCII characters.
  - `void` a type obfuscator.
  - `string` a 128bit string of characters with incorporated length.
  - `memory` a 512bit memory allocator.

Type attributes like `long` and `unsigned` are gone: the idea is to reduce the
alternatives without restricting freedom, by standing on the mantra:

> Few choices, full control.

This is justified by the fact that having many integer or decimal types in modern
programming landscape is not helpful -- embedded systems being a different world,
which is not the one ⚡️ION⚡️ is aiming for.

Also, unsigned integers, while being a nice concept, are a common source of programming
errors, due to the fact that negative values are interpreted as positive: e.g. a 16bit
unsigned integer written in code as `-1` is actually `65535` for the CPU register.
By always using signed integers, the program is less prone to confusion, and at the same
time everything that was possible before, it still is now, without limiting the freedom
of the developer.

Additionally, as you can see by having `memory` in the base types list, ⚡️ION⚡️ treats
memory in a completely different way of what you may be used to see in C programs.
The main idea is to completely avoid memory (anti-)patterns like `malloc` / `free`,
object constructors / destructors, garbage collectors and borrowing models. One of
the main advantages of C is manual memory management: when done right, this can
translate in a fine grained control over your program resource usage. The problem is,
it almost has never been done right. That is way so many programming languages have
been given birth, 99% of whom with the motivation of "memory safety". One can judge if
this endeavor has been worth the trouble. ⚡️ION⚡️, instead, does not want to add (yet)
another programming language, but instead introduces a new approach, which can hopefully
bring peace over this debate: more details on the [specific chapter](doc/memory.md).
