<div align="center">
  <h1>⚡️ION⚡️</h1>
  <h3>Super C harge!</h3>
</div>

## Map

A `map` is an unordered collection of *values* identified by an unique *key*. Contrary
to the [array](array.md) or [vector](vector.md) data structure, the map values can be
retrieved in constant time. This is achieved with the use of a hash function, which is
why this data structure is also referred to as __hash map__.

## Usage

Quick overview of the usage of a map:

```c
struct memory allocator = memory_init(0);
struct map parity = map_init(sizeof(u32), sizeof(bool), 0, &allocator);

u32 even = 4;
u32 odd = 7;

map_set(&parity, &even, &(bool) { true });
map_set(&parity, &odd, &(bool) { false });

print("Is %i even? %i", even, *(bool*) map_get(&parity, &even));
print("Is %i even? %i", odd, *(bool*) map_get(&parity, &odd));

memory_release(&allocator);
```

To initialize a map, call the `map_init` function, which accepts 4 arguments:

  - The size in bytes of the *key* type.
  - The size in bytes of the *value* type.
  - The initial capacity of the map: leave to 0 if not known a priori, otherwise set
    it to the maximum number of keys that you know the map will have.
  - A pointer to a `struct memory` allocator.

This function shall initialize and allocate all the data needed for the map to work.

To set a *key* / *value* pair in the map, call the `map_set` function, which accepts 3
arguments:

  - A pointer to the map.
  - A pointer to the *key*.
  - A pointer to the *value*.

As seen in the example, to use literal *keys* or *values* you can use the
[compound literal](https://gcc.gnu.org/onlinedocs/gcc/Compound-Literals.html), such as:
`(bool) { true }`.

To get the *value* of a *key*, call the `map_get` function, which accepts 2 arguments:

  - A pointer to the map.
  - A pointer to the *key*.

The returned value is `NULL` if the *key* is not found in the map, otherwise it is a
`void` pointer to the *value* address. It is your responsibility to cast it and use it
as the correct *value* type that was used during map initialization. This is a
limitation of the C language.

## Implementation

The map is a struct defined in the following way:

```c
struct map {
  u64             capacity;
  u64             length;
  u64             key_typesize;
  u64             value_typesize;
  void*           keys;
  void*           values;
  u64*            hashes;
  struct memory*  allocator;
};
```
