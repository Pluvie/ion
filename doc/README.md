<div align="center">
  <h1>⚡️ION⚡️</h1>
  <h3>Super C harge!</h3>
</div>

## Documentation

Landing page for all documented ⚡️ION⚡️ features and API.

## Features

- Type safe an fully qualified [Data Structures](#data-structures).
- [Reflection](#reflection) of any C program object.
- [Memory](#memory) management.
- Standardized primitive [Types](#types).

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

### Reflection

TODO

### Memory

TODO
