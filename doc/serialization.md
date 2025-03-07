<div align="center">
  <h1>⚡️ION⚡️</h1>
  <h3>Super C harge!</h3>
</div>

## Serialization

Serialization is the process of converting object data (used by the program) between
different portable formats.

__Ion__ offers some ready to use serializations: binary, JSON, and CSV.

__Ion__ has also adopted an extensible approach where it is easy to set up any kind of
new serialization format: the main reason of this is the introduction of the
[reflection](reflection.md) capability that is usually not available in C programs.

To know more on how to target a new format and create its serialization protocol,
refer to the [guide](#custom-formats) at the bottom.

### Binary

Binary serialization is useful to transmit object data over the network. It has minimal
overhead and it is very easy to compress. The main drawback is that it is not to easy
to grasp and debug by the human being.

To serialize an object in the binary protocol __Ion__ provides the `binary_decode` and
`binary_encode` functions.

### JSON

JSON serialization is widely used in the web to transfer data using the HTTP protocol.
It is humanly very comprehensible, but it has a lot of overhead due to the need to
always specify the object field names.

To serialize an object in the JSON protocol __Ion__ provides the `json_decode` and
`json_encode` functions.

### CSV

CSV serialization is a bit old but still widely used to transfer spreadsheet-like data.
It is humanly very comprehensible, and it has little overhead (the column names are
only in the header line), but it is difficult to use if your data is not prone to
be represented in a columnar fashion: this happens when there are arrays or many
nested fields.

To serialize an object in the JSON protocol __Ion__ provides the `csv_decode` and
`csv_encode` functions.

### Custom Formats

To target a custom format (let's call it `xyz`) and create its serialization protocol
you must implement a specific set of functions.

  - `xyz_decode`
  - `xyz_decode_array`
  - `xyz_decode_pointer`
  - `xyz_decode_primitive`
  - `xyz_decode_sequence`
  - `xyz_decode_struct`
  - `xyz_decode_vector`
  - `xyz_encode`
  - `xyz_encode_array`
  - `xyz_encode_pointer`
  - `xyz_encode_primitive`
  - `xyz_encode_sequence`
  - `xyz_encode_struct`
  - `xyz_encode_vector`

Of these functions, only `xyz_decode` and `xyz_encode` offer public symbols: the other
ones must be `static inline`: this is to both improve code clarity and performance.

All these functions share the same arguments which are:

  - `struct io* source, struct object* target` for the `_decode` family.
  - `struct object* source, struct io* target` for the `_encode` family.

The `struct io` is explained in the [io documentation](io.md). Suffice to say, for the
purpose of this guide, that it is a generic interface for reading / writing data -- be
it on a network, file or memory.

The `struct object` is a representation of a program object containing data (usually
a variable). It is implemented like this:

```c
struct object {
  char* name;
  void* address;
  struct reflect* reflection;
  struct memory* allocator;
};
```

The `name` is usually the variable name as it is seen in the source code. The `address`
is the address of the object in the program memory. The `reflection` is the metadata
used to describe the object structure (its type, fields, constraints, etc.). The
`allocator` is the allocator used to allocate the necessary memory for the object: this
is used only when encoding.
