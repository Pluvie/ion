<div align="center">
  <h1>⚡️ION⚡️</h1>
  <h3>Super C harge!</h3>
</div>

## Documentation

Landing page for all documented ⚡️ION⚡️ features and API.

## Features

- Type safe an fully qualified [Data Structures](#data-structures).
- Standardized primitive [Types](#types).
- [Memory](#memory) management.
- Data formats [Serialization](#serialization).
- [Reflection](#reflection) of any C code object.
- Normalized [IO](#io) through files, sockets, pipes, etc.

### Data Structures

With ⚡️ION⚡️ you can write this C code:

```c
struct rgb {
  int red;
  int green;
  int blue;
};

map<char*, struct rgb> colors = map(char*, struct rgb, {
  { "Violet", { 127, 0, 255 }   },
  { "Pink",   { 255, 192, 203 } },
  { "Lime",   { 32, 205, 32 }   };
});
```

And then operate on it using APIs like:

```c
map_get(&colors, "Pink");
// returns a (struct rgb*) to { 255, 192, 203 }

map_has(&colors, "Orange");
// returns false

map_set(&colors, "Orange", { 255, 165, 0 });
// adds the key/value to the map

map_has(&colors, "Orange");
// returns true
```

⚡️ION⚡️ comes with `list`, `set` and `map` prebuilt data structures, but also exposes
a mechanism that makes extremely trivial to implement any other data structure that you
need.

All data structures can hold *any* type, and are fully type safe: if you pass the wrong
type to any of the API the code won't compile.

To get started and know more about ⚡️ION⚡️ data structures refer to the [relative
documentation](data_structures.md).

### Types

⚡️ION⚡️ wants to simplfy and bring some clarity to C primitive types. Long time C
programmers know that this is a very hard topic, so ⚡️ION⚡️ offers a **very hot** take.
The only primitive types available when programming with ⚡️ION⚡️ library are:

```c
int
dec
str
bool
char
void
```

Both `int` and `char` can be also `unsigned`. That's it.
The reasoning behind this drastic approach are explained and evaluated in the [relative
documentation](types.md) about types.

### Memory

C is infamous for its difficulty in managing memory and providing a safe way to program
against it. While this is true to some extent, it has largely been exaggerated ...
it is only because of C inherent control that gives to the programmer.

### Serialization

### Reflection

### IO

## API
