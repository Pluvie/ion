<div align="center">
  <h1>⚡️ION⚡️</h1>
  <h3>Super C harge!</h3>
</div>

## Introduction

__Ion__ is a C substratum that aims to provide many useful features through *syntax
elegance* and *semantic cohesion*.

## Features

Ion shall provide efficient language constructs to:

  - [serialize](doc/serialization.md) to / from many data formats like JSON, XML, CSV,
    etc. and provide an easy way to create your serialization in any other new format.
  - [standardize data types](doc/data-types.md): integers, decimals, strings, etc.
  - offer ready to use data structures like [arrays](doc/array.md), [maps](doc/map.md)
    and [sets](doc/set.md).
  - enable the introspection of any C language struct through
    [reflection](doc/reflection.md).
  - normalize [io operations](doc/io.md) on files, sockets, and memory objects.
  - introduce a [memory management](doc/memory.md) approach that can revolutionize
    the way C code is written.

and many other minor improvements.

Click on the relevant link to know more about these features.

## Usage

To begin using __Ion__, include it in your sources:

```c
#include <ion/ion.h>
#include <ion/ion.c>
```

And compile your program using the `-D ION_INCLUDED` directive. This shall achieve the
most performance by inlining many function calls. You can of course compile the source
and use it as a linked library but you will not benefit from the function inlining.

### Modules

__Ion__ is organized in modules, each one offering a different feature. You may pick
only the modules that you are interested in when including the library:

```c
/* To include only the VECTOR module. */
#include <ion/modules/vector.h>
#include <ion/modules/vector.c>
```

There are however some dependencies when including modules. This is the full modules
list with their requirements:

| Module                                  | Features                          | Dependencies                |
|-----------------------------------------|-----------------------------------|-----------------------------|
| [CORE](doc/modules/core.md)             | Memory management                 | -                           |
| [ARRAY](doc/modules/array.md)           | Array data structure              | CORE                        |
| [IO](doc/modules/io.md)                 | Input / output interface          | CORE                        |
| [MAP](doc/modules/map.md)               | Map data structure                | CORE                        |
| [RANGE](doc/modules/range.md)           | Numerical ranges                  | CORE                        |
| [STRING](doc/modules/string.md)         | String object                     | CORE                        |
| [TIME](doc/modules/time.md)             | Time and date utilities           | CORE                        |
| [VECTOR](doc/modules/vector.md)         | Vector data structure             | CORE                        |
| [TENSOR](doc/modules/tensor.md)         | Tensor data structure             | CORE, RANGE, VECTOR         |
| [REFLECTION](doc/modules/reflection.md) | Runtime source code introspection | CORE, STRING, ARRAY, VECTOR |
| [BINARY](doc/modules/binary.md)         | Binary protocol serialization     | CORE, IO, REFLECTION        |
| [CSV](doc/modules/csv.md)               | CSV data format serialization     | CORE, IO, REFLECTION        |
| [JSON](doc/modules/json.md)             | JSON data format serialization    | CORE, IO, REFLECTION        |
| [TCP](doc/modules/tcp.md)               | TCP networking utilities          | CORE, IO                    |
| [HTTP](doc/modules/http.md)             | HTTP protocol utilities           | CORE, IO, TCP               |

The most important module is the [CORE](doc/modules/core.md), which is the foundation
to all memory management and is a hard requirement for all other modules.
