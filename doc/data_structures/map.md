<div align="center">
  <h1>⚡️ION⚡️</h1>
  <h3>Super C harge!</h3>
</div>

## [Data Structures] Map

A __map__ is an unordered collection of *values* identified by an unique *key*. Contrary
to the __array__ or __vector__ data structure, the __map__ values can be retrieved in
constant time. This is achieved with the use of a hash function, which is why this
data structure is also referred to as __hash map__.

## Features

Ion shall provide efficient language constructs to:

  - serialize to / from many data formats like JSON, BSON, XML, CSV, etc. and provide an
    easy way to create your serialization in any other new format.
  - standardize data types: integers, decimals, strings, etc.
  - offer ready to use data structures like arrays, maps and sets.
  - enable the introspection of any C language struct through reflection.
  - normalize io operations on files, sockets, and memory objects.

and many other minor improvements.

More documentation on these features is on the way.

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
